/* Copyright (c) 2009-2010 Satoshi Nakamoto
   Copyright (c) 2009-2012 The Koredevelopers
   Copyright (c) 2013-2014 The KoreCoin 2.0 developers */
/* See LICENSE for licensing information */

#include "kore.h"
#include "util.h"
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <string>
#include <cstring>

int coin_port_num = 0;

char const* kore_tor_data_directory(
) {
    static std::string const retrieved = (GetDataDir() / "tor").string();
    return retrieved.c_str();
}

char const* kore_service_directory(
) {
    static std::string const retrieved = (GetDataDir() / "onion").string();
    return retrieved.c_str();
}

int check_interrupted(
) {
    return boost::this_thread::interruption_requested() ? 1 : 0;
}

static boost::mutex initializing;

static std::unique_ptr<boost::unique_lock<boost::mutex> > uninitialized(
    new boost::unique_lock<boost::mutex>(initializing)
);

void set_initialized(
) {
    uninitialized.reset();
}

void wait_initialized(
) {
    boost::unique_lock<boost::mutex> checking(initializing);
}
