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
    class UserStats {
    private:
        int num_sessions, num_sessions_with_switches;
    public:
        UserStats();
        void AddSession(bool has_switch);
        int GetNumSessions() { return num_sessions; }
        int GetNumSessionsWithSwitches() { return num_sessions_with_switches; }
    };
    
    int total_sessions, total_sessions_with_switches;
    // maps user
    map<int, UserStats> user_stats;
public:
    
    virtual void Reset();
    
    virtual void AddTrainingSession(const Session& session);
    
    virtual void FinishTraining();
    
    virtual double GetScore(const Session& session);
    
};

#endif /* defined(__Mathematica__naive_classifier__) */
