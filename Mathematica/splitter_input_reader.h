//
//  splitter_input_reader.h
//  Mathematica
//
//  Created by Akim on 12/10/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__splitter_input_reader__
#define __Mathematica__splitter_input_reader__

#include <set>
#include "input_reader.h"
#include "output_writer.h"
#include "plain_input_reader.h"

using std::set;

const int DAYS_UNDER_OBSERVATION = 27;

class SplitterInputReader : public InputReader {
private:
    set<int> valid_users;
    int num_sessions_total, num_sessions_skipped;
    
    PlainInputReader in;
    OutputWriter test_data_writer;
    vector<int> expected_sessions_with_switches;
    Session* next_session;

    void MoveToNextTrainSession();
    bool is_in_train[DAYS_UNDER_OBSERVATION];
    
    string GetMetadataFileName(const MarkedData& data) const;
    bool IsMetadataPrepared(const MarkedData& data) const;
    void PrepareMetadata(const MarkedData& data) const;
    void LoadMetadata(const MarkedData& data);
public:
    SplitterInputReader(const MarkedData& data, int train_days);
    virtual Session* GetNextSession();
    virtual bool HasNextSession() const;
    PlainInputReader GetTestInput() const;
    vector<int> GetExpectedSessionsWithSwitches() const;
    virtual ~SplitterInputReader();
};

#endif /* defined(__Mathematica__splitter_input_reader__) */
