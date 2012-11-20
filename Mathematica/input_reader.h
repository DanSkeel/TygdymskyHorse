//
//  input_reader.h
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__input_reader__
#define __Mathematica__input_reader__

#include <iostream>

#include "data.h"
using std::ifstream;

class InputReader {
private:
    static const int MAX_LINE_LEN = 1000;
    static const double LOG_EVERY; // 10%
    
    FILE* fin;
    long long file_size;
    long long chars_read;
    double next_log;
    
    bool is_marked;
    bool has_next;
    
    char next_line[MAX_LINE_LEN];
    int pos_in_line;
    
    InputReader();
    
    void GetNextLine();
    int GetNextInt();
    char GetNextChar();
    bool HasNextTokenInString();
public:
    InputReader(const MarkedData& data);
    InputReader(const UnmarkedData& data);
    Session* GetNextSession();
    
    bool HasNextSession() {
        return has_next;
    }
};

#endif /* defined(__Mathematica__input_reader__) */
