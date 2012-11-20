//
//  naive_classifier.cpp
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include "naive_classifier.h"
#include "utils.h"

void NaiveClassifier::Reset() {
    
}

void NaiveClassifier::AddTrainingSession(const Session &session) {
    
}

void NaiveClassifier::FinishTraining() {
    
}

double NaiveClassifier::GetScore(const Session &session) {
    return Utils::GetRandomInteger();
}