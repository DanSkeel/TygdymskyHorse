//
//  naive_classifier.cpp
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include "data.h"
#include "logger.h"
#include "naive_classifier.h"
#include "utils.h"

NaiveClassifier::UserStats::UserStats() :
    num_sessions(), num_sessions_with_switches(0) { }

void NaiveClassifier::UserStats::AddSession(bool has_switch) {
    ++num_sessions;
    if (has_switch) {
        ++num_sessions_with_switches;
    }
}

void NaiveClassifier::Reset() {
    user_stats.clear();
    total_sessions = total_sessions_with_switches = 0;
}

void NaiveClassifier::AddTrainingSession(const Session &session) {
    ++total_sessions;
    int user_id = session.user_id;
    UserStats stats_for_current_user = user_stats[user_id];
    stats_for_current_user.AddSession(session.HasSwitches());
    user_stats[user_id] = stats_for_current_user;
}

void NaiveClassifier::FinishTraining() {
}

double NaiveClassifier::GetScore(const Session &session) {
    UserStats stats = user_stats[session.user_id];
    if (stats.GetNumSessions() == 0) {
        return 0;
    } else {
        return ((double)stats.GetNumSessionsWithSwitches()) / stats.GetNumSessions();
    }
}