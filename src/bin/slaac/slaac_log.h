// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SLAAC_LOG_H
#define SLAAC_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <slaac/slaac_messages.h>

namespace isc {
namespace slaac {

/// @brief Slaac logger.
extern isc::log::Logger slaac_logger;

} // namespace isc::slaac
} // namespace isc

#endif
