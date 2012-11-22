//
//  data.cpp
//  Mathematica
//
//  Created by Akim on 11/19/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include "data.h"

void FileData::Dispose() {
    remove(file_name.c_str());
}

TrainingSet::TrainingSet(const string& set_name) :
    train_data(MarkedData(set_name + "_train")),
    test_data(UnmarkedData(set_name + "_test")),
    test_results_data(MarkedData(set_name + "_test_marked")) { }

void TrainingSet::Dispose() {
    train_data.Dispose();
    test_data.Dispose();
    test_results_data.Dispose();
}

bool Session::HasSwitches() const {
    for (size_t i = 0; i < session_log.size(); ++i) {
        if (session_log[i]->record_type == 'S') {
            return true;
        }
    }
    return false;
}

Session::~Session()  {
    for (size_t i = 0; i < session_log.size(); ++i) {
        delete session_log[i];
    }
}