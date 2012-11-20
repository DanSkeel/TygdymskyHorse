//
//  output_writer.h
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__output_writer__
#define __Mathematica__output_writer__

#include <iostream>
#include "data.h"
using std::ofstream;

class OutputWriter {
private:
    FILE* fout;
    bool is_marked;
public:
    OutputWriter(const MarkedData& data);
    OutputWriter(const UnmarkedData& data);
    void Print(const Session& session);
    void Close();
    
};

#endif /* defined(__Mathematica__output_writer__) */
