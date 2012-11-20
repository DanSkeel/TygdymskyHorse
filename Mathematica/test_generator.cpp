//
//  test_generator.cpp
//  Mathematica
//
//  Created by Akim on 11/19/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include <cstdio>
#include "input_reader.h"
#include "output_writer.h"
#include "test_generator.h"
#include "utils.h"


MarkedData TestGenerator::GenerateSubTest(const MarkedData& sample_data,
                                          double sample_ratio,
                                          const string& subtest_file_name) {
    unsigned int k = Utils::GetRandomInteger();
    unsigned int b = Utils::GetRandomInteger();
    
    MarkedData result(subtest_file_name);
    InputReader in(sample_data);
    OutputWriter out(result);
    while (in.HasNextSession()) {
        Session* session = in.GetNextSession();
        unsigned int user_id = session->user_id;
        unsigned int hash = user_id * k + b;
        double goodness = (double)hash / (1LL << 32);
        if (goodness < sample_ratio) {
            out.Print(*session);
        }
        delete session;
    }
    out.Close();
    return result;
}

MarkedData TestGenerator::GenerateSubTest(const MarkedData &sample_data,
                                          double sample_ratio) {
    return GenerateSubTest(sample_data, sample_ratio, "_" + Utils::GetRandomString(10));
}

TrainingSet TestGenerator::SplitTest(const MarkedData& sample_data,
                                     double train_ratio) {
    unsigned int k = Utils::GetRandomInteger();
    unsigned int b = Utils::GetRandomInteger();
    
    TrainingSet result(Utils::GetRandomString(10));
    InputReader in(sample_data);
    OutputWriter out_train(result.train_data);
    OutputWriter out_test(result.test_data);
    OutputWriter out_test_results(result.test_results_data);
    while (in.HasNextSession()) {
        Session* session = in.GetNextSession();
        unsigned int session_id = session->session_id;
        unsigned int hash = session_id * k + b;
        double goodness = (double)hash / (1LL << 32);
        if (goodness < train_ratio) {
            out_train.Print(*session);
        } else {
            out_test.Print(*session);
            out_test_results.Print(*session);
        }
        delete session;
    }
    out_train.Close();
    out_test.Close();
    out_test_results.Close();
    return result;
}
