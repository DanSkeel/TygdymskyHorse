//
//  utils.h
//  Mathematica
//
//  Created by Akim on 11/19/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__utils__
#define __Mathematica__utils__

#include <iostream>
#include <string>
using std::string;

class Utils {
public:
    static char GetRandomChar();
    static string GetRandomString(int len);
    static int GetRandomInteger();
    static long long GetFileSize(const string& file_name);
};

#endif /* defined(__Mathematica__utils__) */
