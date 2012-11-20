//
//  logger.cpp
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include <iostream>
#include "logger.h"
using std::cerr;
using std::endl;

int Logger::LOG_LEVEL = 0;

void Logger::SetLogLevel(int new_log_level) {
    LOG_LEVEL = new_log_level;
}

void Logger::Log(const string &message, int message_log_level) {
    if (LOG_LEVEL < message_log_level) {
        cerr << message << endl;
    }
}