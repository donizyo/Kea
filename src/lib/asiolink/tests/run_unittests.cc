// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <util/unittests/run_all.h>
#include <log/logger_manager.h>

int
main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);         // Initialize Google test
    isc::log::LoggerManager::init("unittest");      // Set a root logger name
    return (isc::util::unittests::run_all());
}
