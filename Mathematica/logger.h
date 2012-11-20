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

class Logger {
private:
    static int LOG_LEVEL;
public:
    static void SetLogLevel(int new_log_level);
    static void Log(const string& message, int log_level);
    
    static void Debug(const string& message) {
        Log(message, 0);
    }
    
    static void Info(const string& message) {
        Log(message, 20);
    }
    
    static void Warning(const string& message) {
        Log(message, 40);
    }
    
    static void Error(const string& message) {
        Log(message, 60);
    }
    
    static void Fatal(const string& message) {
        Log(message, 80);
        exit(1);
    }
};

#endif /* defined(__Mathematica__logger__) */
