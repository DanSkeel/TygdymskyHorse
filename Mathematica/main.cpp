//
//  main.cpp
//  Mathematica
//
//  Created by Akim on 11/19/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include <iostream>
#include "logger.h"
#include "naive_classifier.h"
#include "test_generator.h"
#include "quality_tester.h"
using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    Logger::SetLogLevel(0); // Logging everything.
//    TestGenerator::GenerateSubTest(MarkedData("train"), 0.10, "_train_10_percent");

    NaiveClassifier naive;
//    QualityTester q(MarkedData("_train_1_percent"), &naive);
//    std::cout << q.Test(24.0 / 27.0);
    naive.TrainOn(MarkedData("train"));
    vector<int> res = naive.TestOn(UnmarkedData("test"));
    freopen("test_ans", "wb", stdout);
    for (size_t i = 0; i < res.size(); ++i) {
        printf("%d\n", res[i]);
    }
    return 0;
}

