//
//  quality_tester.h
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__quality_tester__
#define __Mathematica__quality_tester__

#include <iostream>
#include "classifier.h"

class QualityTester {
private:
    MarkedData data;
    Classifier* classifier;
    double GetScore(vector<int> received_results, const vector<int>& sessions_with_switches);
    
public:
    QualityTester(const MarkedData &data, Classifier* classifier) :
    data(data), classifier(classifier) { }
    
    double Test(int train_days);
};

#endif /* defined(__Mathematica__quality_tester__) */
