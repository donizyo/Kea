// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <kea_version.h>

#include <d2/parser_context.h>

#include <fstream>
#include <iostream>

using namespace isc;
using namespace isc::data;
using namespace std;

/// @file Just apply the D2 parser from the input file and pretty print
/// the result to the output file.

/// @brief Print parser2 usage.
void
usage() {
    cerr << "Usage: parser2 [-v] [-V] -i <input> -o <output>" << endl;
}

int
main(int argc, char* argv[]) {
    string input_file("");
    string output_file("");

    int ch;
    while ((ch = getopt(argc, argv, "i:o:vV")) != -1) {
        switch (ch) {
        case 'i':
            input_file = optarg;
            break;

        case 'o':
            output_file = optarg;
            break;

        case 'v':
            cout << VERSION << endl;
            return (EXIT_SUCCESS);

        case 'V':
            cout << VERSION << endl << EXTENDED_VERSION << endl;
            return (EXIT_SUCCESS);

        default:
            usage();
            return (EXIT_FAILURE);
        }
    }

    // Check for extraneous parameters.
    if (argc > optind) {
        usage();
        return (EXIT_FAILURE);
    }

    // Input file is required.
    if (input_file.empty()) {
        cerr << "Input file was not specified." << endl;
        usage();
        return (EXIT_FAILURE);
    }

    try {
        D2ParserContext parser;
        ConstElementPtr json;
        json = parser.parseFile(input_file, D2ParserContext::PARSER_DHCPDDNS);
        if (!json) {
            cerr << "No input found" << endl;
            return (EXIT_FAILURE);
        }

        if (output_file.empty()) {
            cout << prettyPrint(json) << endl;
        } else {
            ofstream out(output_file, ios::trunc);
            if (!out.good()) {
                isc_throw(Unexpected, "Unable to open file " + output_file +
                          " for writing");
                out << prettyPrint(json) << endl;
            }
            out.close();
        }
    } catch (const std::exception& ex) {
        cerr << "parser2 failed with " << ex.what() << endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}