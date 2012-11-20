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
#include "pointwise_classifier.h"

class NaiveClassifier : public PointwiseClassifier {
    virtual void Reset();
    
    virtual void AddTrainingSession(const Session& session);
    
    virtual void FinishTraining();
    
    virtual double GetScore(const Session& session);
    
};

#endif /* defined(__Mathematica__naive_classifier__) */
