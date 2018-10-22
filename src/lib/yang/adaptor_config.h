// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_ADAPTOR_CONFIG_H
#define ISC_ADAPTOR_CONFIG_H 1

#include <yang/adaptor_host.h>
#include <yang/adaptor_option.h>
#include <yang/adaptor_pool.h>
#include <yang/adaptor_subnet.h>
#include <list>

namespace isc {
namespace yang {

/// @brief JSON adaptor for Kea server configurations.
///
/// Currently only from JSON to YANG for DHCPv4 and DHCPv6 available
/// as preProcess4 and preProcess6 class methods, filling some required
/// (by YANG) fields (e.g. subnet IDs, or option code and space), or
/// transforming a hand-written JSON configuration into a canonical form.
class AdaptorConfig : public AdaptorHost, public AdaptorOption,
    public AdaptorSubnet {
public:

    /// @brief Constructor.
    AdaptorConfig();

    /// @brief Destructor.
    virtual ~AdaptorConfig();

    /// @brief Pre process a DHCPv4 configuration.
    ///
    /// Assign subnet IDs, check and set default in options.
    ///
    /// @param config The configuration.
    /// @throw MissingKey when a required key is missing.
    /// @throw BadValue when null or not a map
    /// @note Does nothing if "Dhcp4" is not present in the map.
    static void preProcess4(isc::data::ConstElementPtr config);

    /// @brief Pre process a DHCPv6 configuration.
    ///
    /// Assign subnet IDs, check and set default in options.
    ///
    /// @param config The configuration.
    /// @throw MissingKey when a required key is missing.
    /// @throw BadValue when null or not a map
    /// @note Does nothing if "Dhcp6" is not present in the map.
    static void preProcess6(isc::data::ConstElementPtr config);

protected:
    /// @brief collectID applied to a subnet list.
    ///
    /// @param subnets The subnet list.
    /// @param set The reference to the set of assigned IDs.
    /// @return True if all subnets have an ID, false otherwise.
    static bool subnetsCollectID(isc::data::ConstElementPtr subnets,
                                 SubnetIDSet& set);

    /// @brief collectID applied to a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param set The reference to the set of assigned IDs.
    /// @param subsel The subnet list name.
    /// @return True if all subnets have an ID, false otherwise.
    static bool sharedNetworksCollectID(isc::data::ConstElementPtr networks,
                                        SubnetIDSet& set,
                                        const std::string& subsel);

    /// @brief assignID applied to a subnet list.
    ///
    /// @param subnets The subnet list.
    /// @param set The reference to the set of assigned IDs.
    /// @param next The next ID.
    /// @return True if all subnets have an ID, false otherwise.
    static void subnetsAssignID(isc::data::ConstElementPtr subnets,
                                SubnetIDSet& set, isc::dhcp::SubnetID& next);

    /// @brief assignID applied to a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param set The reference to the set of assigned IDs.
    /// @param next The next ID.
    /// @param subsel The subnet list name.
    /// @return True if all subnets have an ID, false otherwise.
    static void sharedNetworksAssignID(isc::data::ConstElementPtr networks,
                                       SubnetIDSet& set,
                                       isc::dhcp::SubnetID& next,
                                       const std::string& subsel);

    /// @brief canonizePool applied to a pool list.
    ///
    /// @param pools The pool list.
    static void canonizePools(isc::data::ConstElementPtr pools);

    /// @brief canonizePool applied to a subnet list.
    ///
    /// @param subnets The subnet list.
    static void poolSubnets(isc::data::ConstElementPtr subnets);

    /// @brief canonizePool applied to a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param subsel The subnet list name.
    static void poolShareNetworks(isc::data::ConstElementPtr networks,
                                  const std::string& subsel);

    /// @brief Collect option definitions from an option definition list.
    ///
    /// @param defs The option definition list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionDefList(isc::data::ConstElementPtr defs,
                              const std::string& space,
                              OptionCodes& codes);

    /// @brief Set missing option codes to an option data list.
    ///
    /// @param options The option data list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionDataList(isc::data::ConstElementPtr options,
                               const std::string& space,
                               const OptionCodes& codes);

    /// @brief Collect option definitions from a client class list
    /// and set missing option codes.
    ///
    /// @param classes The client class list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionClasses(isc::data::ConstElementPtr classes,
                              const std::string& space,
                              OptionCodes& codes);

    /// @brief Set missing option codes to a pool list.
    ///
    /// @param pools The pool list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionPools(isc::data::ConstElementPtr pools,
                            const std::string& space,
                            const OptionCodes& codes);

    /// @brief Set missing option codes to a host reservation list.
    ///
    /// @param hosts The host reservation list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionHosts(isc::data::ConstElementPtr hosts,
                            const std::string& space,
                            const OptionCodes& codes);

    /// @brief Set missing option codes to a subnet list.
    ///
    /// @param subnets The subnet list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionSubnets(isc::data::ConstElementPtr subnets,
                              const std::string& space,
                              const OptionCodes& codes);

    /// @brief Set missing option codes to a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionSharedNetworks(isc::data::ConstElementPtr networks,
                                     const std::string& space,
                                     const OptionCodes& codes);

    /// @brief Process require client classes in a pool list.
    ///
    /// Remove empty require client class list.
    ///
    /// @param pools The pool list.
    static void requireClassesPools(isc::data::ConstElementPtr pools);

    /// @brief Process require client classes in a subnet list.
    ///
    /// Remove empty require client class lists.
    ///
    /// @param subnets The subnet list.
    static void requireClassesSubnets(isc::data::ConstElementPtr subnets);

    /// @brief Process require client classes in a shared network list.
    ///
    /// Remove empty require client class lists.
    ///
    /// @param networks The shared network list.
    /// @param subsel The subnet list name.
    static void requireClassesSharedNetworks(isc::data::ConstElementPtr networks,
                                             const std::string& subsel);

    /// @brief Process host reservation list.
    ///
    /// Quote when needed flex-id identifiers.
    ///
    /// @param hosts The host reservation list.
    static void hostList(isc::data::ConstElementPtr hosts);

    /// @brief Process host reservations in a subnet list.
    ///
    /// Quote when needed flex-id identifiers.
    ///
    /// @param subnets The subnet list.
    static void hostSubnets(isc::data::ConstElementPtr subnets);

    /// @brief Process host reservations in a shared network list.
    ///
    /// Quote when needed flex-id identifiers.
    ///
    /// @param networks The shared network list.
    /// @param space The default space name.
    static void hostSharedNetworks(isc::data::ConstElementPtr networks,
                                   const std::string& space);

    /// @brief updateRelay in a subnet list.
    ///
    /// Force the use of ip-addresses when it finds an ip-address entry.
    ///
    /// @param subnets The subnet list.
    static void relaySubnets(isc::data::ConstElementPtr subnets);

    /// @brief updateRelay in a shared network list.
    ///
    /// Force the use of ip-addresses when it finds an ip-address entry.
    ///
    /// @param networks The shared network list.
    /// @param subsel The subnet list name.
    static void relaySharedNetworks(isc::data::ConstElementPtr networks,
                                    const std::string& subsel);

    /// @brief Update (hosts) database.
    ///
    /// Force the use of hosts-databases vs. hosts-database.
    ///
    /// @param dhcp The DHCP server.
    static void updateDatabase(isc::data::ConstElementPtr dhcp);

    /// @brief Update relay supplied options.
    ///
    /// Remove empty relay supplied option list.
    ///
    /// @param dhcp The DHCPv6 server.
    static void relaySuppliedOptions(isc::data::ConstElementPtr dhcp);

    /// @brief Pre process a configuration.
    ///
    /// Assign subnet IDs, check and set default in options, etc.
    ///
    /// @param dhcp The server configuration.
    /// @param subsel The subnet list name.
    /// @param space The default option space name.
    /// @throw MissingKey when a required key is missing.
    static void preProcess(isc::data::ConstElementPtr dhcp,
                           const std::string& subsel,
                           const std::string& space);
};

}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_ADAPTOR_CONFIG_H
