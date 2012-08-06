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

#ifndef DATASRC_MEMORY_RDATA_READER_H
#define DATASRC_MEMORY_RDATA_READER_H 1

#include <boost/function.hpp>

namespace isc {
namespace dns{
class LabelSequence;
class RRClass;
class RRType;
}
namespace datasrc {
namespace memory {

class RDataReader {
public:
    // The sequence and attributes
    typedef boost::function<void(const dns::LabelSequence&, unsigned int)>
        NameAction;
    typedef boost::function<void(const uint8_t*, size_t)> DataAction;

    // For the default parameters.
    static void emptyNameAction(const dns::LabelSequence& label,
                                unsigned int attributes);
    static void emptyDataAction(const uint8_t* data, size_t size);

    RDataReader(const dns::RRClass& rrclass, const dns::RRType& rrtype,
                size_t size, const uint8_t* data,
                const NameAction& name_action = &emptyNameAction,
                const DataAction& data_action = &emptyDataAction);

    enum Action {
        NAME,
        DATA,
        END
    };

    class Result {
    public:
        Action action() const;
        const uint8_t* data() const;
        size_t size() const;
        const dns::LabelSequence& sequence;
        operator bool() const {
            return (action() != END);
        }
    };

    Result next();
    void rewind();

    size_t getSize() const;
};

}
}
}

#endif
