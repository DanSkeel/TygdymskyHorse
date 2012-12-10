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
public:
    virtual bool HasNextSession() const = 0;
    virtual Session* GetNextSession() = 0;
    virtual ~InputReader() { }
};

#endif /* defined(__Mathematica__input_reader__) */
