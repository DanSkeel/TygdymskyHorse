//
//  classifier.cpp
//  Mathematica
//
//  Created by Akim on 11/22/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include "classifier.h"
#include "input_reader.h"
#include "logger.h"

void Classifier::TrainOn(const MarkedData &data) {
    Logger::Info << "Training classifier\n";
    Reset();
    InputReader in(data);
    while (in.HasNextSession()) {
        Session* session = in.GetNextSession();
        AddTrainingSession(*session);
        delete session;
    }
    Logger::Info << "Finishing training\n";
    FinishTraining();
}

vector<int> Classifier::TestOn(const UnmarkedData& data) {
    InputReader in = InputReader(data);
    while (in.HasNextSession()) {
        Session* session = in.GetNextSession();
        AddTestSession(*session);
        delete session;
    }
    Logger::Info << "Getting classification results\n";
    return FinishTesting();
}