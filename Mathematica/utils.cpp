//
//  utils.cpp
//  Mathematica
//
//  Created by Akim on 11/19/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "utils.h"

char Utils::GetRandomChar() {
    return rand() % 26 + 'a';
}

string Utils::GetRandomString(int len) {
    string res = "";
    for (int i = 0; i < len; ++i) {
        res.push_back(GetRandomChar());
    }
    return res;
}

int Utils::GetRandomInteger() {
    int ans = 0;
    for (int i = 0; i < 8; ++i) {
        ans = ans * RAND_MAX + rand();
    }
    return ans;
}

long long Utils::GetFileSize(const string &file_name) {
    std::ifstream in(file_name.c_str(), std::ifstream::in | std::ifstream::binary);
    in.seekg(0, std::ifstream::end);
    return (long long)in.tellg();
}