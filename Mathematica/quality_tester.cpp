//
//  quality_tester.cpp
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include <algorithm>
#include <vector>
#include "data.h"
#include "input_reader.h"
#include "logger.h"
#include "test_generator.h"
#include "quality_tester.h"
using std::binary_search;
using std::cerr;
using std::endl;
using std::vector;

double QualityTester::GetScore(vector<int> received_results, const vector<int>& sessions_with_switches) {
    long long num_ones_found = 0;
    long long num_inversions = 0;
    for (size_t i = 0; i < received_results.size(); ++i) {
        if (binary_search(sessions_with_switches.begin(), sessions_with_switches.end(), received_results[i])) {
            ++num_ones_found;
        } else {
            num_inversions += num_ones_found;
        }
    }
    long long num_pairs = num_ones_found * (received_results.size() - num_ones_found);
    return ((double)num_inversions) / num_pairs;
}

double QualityTester::Test(double train_ratio) {
    Logger::Info("Splitting data");
    TrainingSet training_set = TestGenerator::SplitTest(data, train_ratio);
    Logger::Info("Training classifier");
    classifier->Reset();
    InputReader in(training_set.train_data);
    while (in.HasNextSession()) {
        Session* session = in.GetNextSession();
        classifier->AddTrainingSession(*session);
        delete session;
    }
    Logger::Info("Finishing training");
    classifier->FinishTraining();
    Logger::Info("Loading test data");
    in = InputReader(training_set.test_data);
    while (in.HasNextSession()) {
        Session* session = in.GetNextSession();
        classifier->AddTestSession(*session);
        delete session;
    }
    Logger::Info("Getting classification results");
    vector<int> received_results = classifier->FinishTesting();

    Logger::Info("Getting expected results");
    vector<int> sessions_with_switches;
    in = InputReader(training_set.test_results_data);
    while (in.HasNextSession()) {
        Session* session = in.GetNextSession();
        if (session->HasSwitches()) {
            sessions_with_switches.push_back(session->session_id);
        }
        delete session;
    }
    sort(sessions_with_switches.begin(), sessions_with_switches.end());
    Logger::Info("Getting final score");
    double score = GetScore(received_results, sessions_with_switches);
    training_set.Dispose();
    return score;
}