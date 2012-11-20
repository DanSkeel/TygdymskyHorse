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
//    TestGenerator::GenerateSubTest(MarkedData("train"), 0.01, "_train_1_percent");

    NaiveClassifier naive;
    QualityTester q(MarkedData("_train_1_percent"), &naive);
    std::cout << q.Test(0.9);
    return 0;
}

