//
//  pointwise_classifier.h
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef Mathematica_pointwise_classifier_h
#define Mathematica_pointwise_classifier_h

#include <algorithm>
#include <vector>
#include "classifier.h"
#include "data.h"
using std::make_pair;
using std::pair;
using std::vector;

class PointwiseClassifier : public Classifier {
private:
    vector<pair<double, int> > classification_results;
    virtual double GetScore(const Session& session) = 0;
    
public:
    virtual void AddTestSession(const Session& session) {
        double score = GetScore(session);
        classification_results.push_back(make_pair(score, session.session_id));
    }
    virtual vector<int> FinishTesting() {
        sort(classification_results.begin(), classification_results.end());
        reverse(classification_results.begin(), classification_results.end());
        vector<int> result;
        for (size_t i = 0; i < classification_results.size(); ++i) {
            result.push_back(classification_results[i].second);
        }
        return result;
    }
};

#endif
