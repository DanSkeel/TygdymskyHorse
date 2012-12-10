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

void Classifier::TrainOn(InputReader *in) {
    Logger::Info << "Training classifier\n";
    Reset();
    while (in->HasNextSession()) {
        Session* session = in->GetNextSession();
        AddTrainingSession(*session);
        delete session;
    }
    Logger::Info << "Finishing training\n";
    FinishTraining();
}

vector<int> Classifier::TestOn(InputReader *in) {
    while (in->HasNextSession()) {
        Session* session = in->GetNextSession();
        AddTestSession(*session);
        delete session;
    }
    Logger::Info << "Getting classification results\n";
    return FinishTesting();
}