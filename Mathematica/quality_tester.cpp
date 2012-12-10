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
#include "logger.h"
#include "plain_input_reader.h"
#include "quality_tester.h"
#include "splitter_input_reader.h"
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

double QualityTester::Test(int train_days) {
    SplitterInputReader in(data, train_days);
    Logger::Info << "Splitting data\n";
    classifier->TrainOn(&in);
    Logger::Info << "Loading test data\n";
    PlainInputReader test_input = in.GetTestInput();
    vector<int> received_results = classifier->TestOn(&test_input);

    Logger::Info << "Getting expected results\n";
    vector<int> sessions_with_switches = in.GetExpectedSessionsWithSwitches();
    sort(sessions_with_switches.begin(), sessions_with_switches.end());
    Logger::Info << "Getting final score\n";
    double score = GetScore(received_results, sessions_with_switches);
    return score;
}