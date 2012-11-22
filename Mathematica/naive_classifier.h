//
//  naive_classifier.h
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__naive_classifier__
#define __Mathematica__naive_classifier__

#include <iostream>
#include <map>
#include "pointwise_classifier.h"
using std::map;
using std::pair;

class NaiveClassifier : public PointwiseClassifier {
private:
    int total_sessions, total_sessions_with_switches;
    map<int, pair<int, int> > user_stats;
public:
    
    virtual void Reset();
    
    virtual void AddTrainingSession(const Session& session);
    
    virtual void FinishTraining();
    
    virtual double GetScore(const Session& session);
    
};

#endif /* defined(__Mathematica__naive_classifier__) */
