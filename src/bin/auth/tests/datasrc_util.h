// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef AUTH_DATA_SOURCE_UTIL_H
#define AUTH_DATA_SOURCE_UTIL_H 1

#include <dns/name.h>
#include <dns/rrclass.h>

#include <istream>

namespace isc {
namespace auth {
namespace unittest {

/// \brief Create an SQLite3 database file for a given zone from a stream.
///
/// This function creates an SQLite3 DB file for the specified zone
/// with specified content.  The zone will be created in the given
/// SQLite3 database file.  The database file does not have to exist;
/// this function will automatically create a new file for the test
/// based on a template that only contains the necessary schema. If
/// the given file already exists this function overrides the content
/// (so basically the file must be an ephemeral one only for that test
/// case).
///
/// The input stream must produce strings as the corresponding
/// \c dns::masterLoad() function expects.
///
/// \param zclass The RR class of the zone
/// \param zname The origin name of the zone
/// \param db_file The SQLite3 data base file in which the zone data should be
/// installed.
/// \param rr_stream An input stream that produces zone data.
void
createSQLite3DB(dns::RRClass zclass, const dns::Name& zname,
                const char* const db_file, std::istream& rr_stream);

} // end of unittest
} // end of auth
} // end of isc

#endif  // AUTH_DATA_SOURCE_UTIL_H

// Local Variables:
// mode: c++
// End:
