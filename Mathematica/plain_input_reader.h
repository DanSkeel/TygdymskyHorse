//
//  plain_input_reader.h
//  Mathematica
//
//  Created by Akim on 12/10/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__plain_input_reader__
#define __Mathematica__plain_input_reader__

#include "input_reader.h"

class PlainInputReader : public InputReader {
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
    
    PlainInputReader();
    
    void GetNextLine();
    int GetNextInt();
    char GetNextChar();
    bool HasNextTokenInString();
public:
    PlainInputReader(const MarkedData& data);
    PlainInputReader(const UnmarkedData& data);
    virtual Session* GetNextSession();
    
    virtual bool HasNextSession() const {
        return has_next;
    }
};

#endif /* defined(__Mathematica__plain_input_reader__) */
