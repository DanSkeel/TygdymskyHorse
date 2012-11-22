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
LoggerWithLevel Logger::Debug = LoggerWithLevel(20);
LoggerWithLevel Logger::Info = LoggerWithLevel(40);
LoggerWithLevel Logger::Warning = LoggerWithLevel(60);
LoggerWithLevel Logger::Error = LoggerWithLevel(80);
LoggerWithLevel Logger::Fatal = LoggerWithLevel(100);

void Logger::SetLogLevel(int new_log_level) {
    LOG_LEVEL = new_log_level;
}

int Logger::GetLogLevel() {
    return LOG_LEVEL;
}

LoggerWithLevel Logger::GetLogger(int level) {
    return LoggerWithLevel(level);
}
