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

void NaiveClassifier::Reset() {
    user_stats.clear();
    total_sessions = total_sessions_with_switches = 0;
}

void NaiveClassifier::AddTrainingSession(const Session &session) {
    ++total_sessions;
    int user_id = session.user_id;
    pair<int, int> res = user_stats[user_id];
    ++res.second;
    if (session.HasSwitches()) {
        ++total_sessions_with_switches;
        ++res.first;
    }
    user_stats[user_id] = res;
}

void NaiveClassifier::FinishTraining() {
    map<int, int> user_counts;
    for (map<int, pair<int, int> >::iterator tmp = user_stats.begin(); tmp != user_stats.end(); ++tmp) {
        ++user_counts[tmp->second.second];
    }
    for (map<int, int>::iterator tmp = user_counts.begin(); tmp != user_counts.end(); ++tmp) {
        Logger::Info << tmp->first << " - " << tmp->second << "\n";
    }
}

double NaiveClassifier::GetScore(const Session &session) {
    pair<int, int> stats = user_stats[session.user_id];
    if (stats.first == 0) {
        return 1;//(total_sessions_with_switches + 0.0) / total_sessions;
    } else {
        return (stats.first + 0.0) / stats.second;
    }
}