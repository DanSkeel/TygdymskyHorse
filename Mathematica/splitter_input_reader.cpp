//
//  splitter_input_reader.cpp
//  Mathematica
//
//  Created by Akim on 12/10/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include <cassert>
#include <fstream>
#include <map>
#include <set>
#include "logger.h"
#include "splitter_input_reader.h"
#include "utils.h"

using std::map;
using std::pair;
using std::set;

string SplitterInputReader::GetMetadataFileName(const MarkedData &data) const {
    return data.file_name + "_metadata.txt";
}

bool SplitterInputReader::IsMetadataPrepared(const MarkedData &data) const {
    std::ifstream try_input(GetMetadataFileName(data));
    return (bool) try_input;
}

void SplitterInputReader::PrepareMetadata(const MarkedData &data) const {
    //map<int, set<int> > users_to_sessions; // maps user_id to set of all days where any sessions are found
    map<int, set<int> > users_to_sessions_with_switches; // same but only sessions with switches are counted
    set<int> user_ids;
    PlainInputReader temp_input(data);
    while (temp_input.HasNextSession()) {
        Session* s = temp_input.GetNextSession();
        user_ids.insert(s->user_id);
    //    users_to_sessions[s->user_id].insert(s->day_id);
        if (s->HasSwitches()) {
            users_to_sessions_with_switches[s->user_id].insert(s->day_id);
        }
        delete s;
    }
    FILE* out_file = fopen(GetMetadataFileName(data).c_str(), "wb");
    fprintf(out_file, "%d\n", (int)user_ids.size());
    for (set<int>::iterator it = user_ids.begin(); it != user_ids.end(); ++it) {
        int user_id = *it;
        fprintf(out_file, "%d", user_id);
        set<int> days;
        /*
        days = users_to_sessions[user_id];
        fprintf(out_file, " %d", (int)days.size());
        for (set<int>::iterator it2 = days.begin(); it2 != days.end(); ++it2) {
            fprintf(out_file, " %d", *it2);
        }
         */
        
        days = users_to_sessions_with_switches[user_id];
        fprintf(out_file, " %d", (int)days.size());
        for (set<int>::iterator it2 = days.begin(); it2 != days.end(); ++it2) {
            fprintf(out_file, " %d", *it2);
        }
        fprintf(out_file, "\n");
    }
    fclose(out_file);
    
}

void SplitterInputReader::LoadMetadata(const MarkedData &data) {
    int users_total = 0, users_skipped = 0;
    Logger::Info << "Loading metadata\n";
    FILE* metadata_file = fopen(GetMetadataFileName(data).c_str(), "rb");
    int num_user_ids;
    fscanf(metadata_file, "%d", &num_user_ids);
    for (int i = 0; i < num_user_ids; ++i) {
        ++users_total;
        int user_id;
        int num_days_with_switches;
        fscanf(metadata_file, "%d%d", &user_id, &num_days_with_switches);
        bool has_switches_in_train_period = false;
        for (int j = 0; j < num_days_with_switches; ++j) {
            int day_id;
            fscanf(metadata_file, "%d", &day_id);
            if (is_in_train[day_id - 1]) {
                has_switches_in_train_period = true;
            }
        }
        if (has_switches_in_train_period) {
            valid_users.insert(user_id);
        } else {
            ++users_skipped;
        }
    }
    fclose(metadata_file);
    Logger::Info << "Metadata loaded. Skipping " << users_skipped << " users ("
                << (double)users_skipped * 100.0 / users_total << "%)\n";
}

SplitterInputReader::SplitterInputReader(const MarkedData& data, int train_days) :
    test_data_writer(UnmarkedData("_" + Utils::GetRandomString(10))),
    in(PlainInputReader(data)) {
        num_sessions_total = num_sessions_skipped = 0;
        expected_sessions_with_switches.clear();
        vector<int> days_priority(DAYS_UNDER_OBSERVATION);
        for (int i = 0; i < DAYS_UNDER_OBSERVATION; ++i) {
            days_priority[i] = i;
            is_in_train[i] = false;
        }
        random_shuffle(days_priority.begin(), days_priority.end());
        for (int i = 0; i < train_days; ++i) {
            is_in_train[days_priority[i]] = true;
        }

        
        if (!IsMetadataPrepared(data)) {
            Logger::Info << "\nMetadata not prepared. Preparing it now (will be run once)\n";
            PrepareMetadata(data);
            Logger::Info << "Metadata prepared\n";
        }
        LoadMetadata(data);
        
        next_session = NULL;
        MoveToNextTrainSession();
}

PlainInputReader SplitterInputReader::GetTestInput() const {
    UnmarkedData data(test_data_writer.GetFileName());
    return PlainInputReader(UnmarkedData(test_data_writer.GetFileName()));
}

SplitterInputReader::~SplitterInputReader() {
    Logger::Error << "Skipped " << num_sessions_skipped << " sessions (" <<
        ((double)num_sessions_skipped * 100.0) / num_sessions_total << "%)\n";
    if (next_session != NULL) {
        delete next_session;
    }
    UnmarkedData(test_data_writer.GetFileName()).Dispose();
}

bool SplitterInputReader::HasNextSession() const {
    return next_session != NULL;
}

void SplitterInputReader::MoveToNextTrainSession() {
    while (in.HasNextSession()) {
        ++num_sessions_total;
        Session* s = in.GetNextSession();
        if (!valid_users.count(s->user_id)) {
            ++num_sessions_skipped;
            // Invalid user. Skipping.
            continue;
        }
        int day_id = s->day_id ;
        assert(day_id > 0 && day_id <= DAYS_UNDER_OBSERVATION);
        if (is_in_train[day_id - 1]) {
            next_session = s;
            return;
        } else {
            test_data_writer.Print(*s);
            if (s->HasSwitches()) {
                expected_sessions_with_switches.push_back(s->session_id);
            }
            delete s;
        }
    }
    next_session = NULL;
    // End of sessions
    test_data_writer.Close();
}

Session* SplitterInputReader::GetNextSession() {
    Session* s = next_session;
    MoveToNextTrainSession();
    return s;
}

vector<int> SplitterInputReader::GetExpectedSessionsWithSwitches() const {
    return expected_sessions_with_switches;
}