//
//  logger.h
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__logger__
#define __Mathematica__logger__

#include <iostream>
#include <string>
using std::string;

class LoggerWithLevel;

class Logger {
private:
    static int LOG_LEVEL;
public:
    static void SetLogLevel(int new_log_level);
    static int GetLogLevel();
    
    static LoggerWithLevel Debug;
    static LoggerWithLevel Info;
    static LoggerWithLevel Warning;
    static LoggerWithLevel Error;
    static LoggerWithLevel Fatal;
    
    static LoggerWithLevel GetLogger(int level);
    
};

class LoggerWithLevel {
private:
    int level = 0;
public:
    LoggerWithLevel(int level) : level(level) { }
    
    template<class T>
    friend LoggerWithLevel operator << (const LoggerWithLevel &logger,
                                        const T& message) {
        if (Logger::GetLogLevel() <= logger.level) {
            std::cerr << message;
            std::cerr.flush();
        }
        return logger;
    }
            
};

#endif /* defined(__Mathematica__logger__) */
