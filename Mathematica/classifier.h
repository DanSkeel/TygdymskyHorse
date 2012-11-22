//
//  classifier.h
//  Mathematica
//
//  Created by Akim on 11/22/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__classifier__
#define __Mathematica__classifier__

#include <vector>
#include "data.h"
using std::vector;

class Classifier {
private:
    // Инициализирует классификатор. Гарантируется, что эта функция будет вызвана
    // до начала подачи данных.
    virtual void Reset() = 0;
    
    // Добавление очередного обучающего примера.
    virtual void AddTrainingSession(const Session& session) = 0;
    
    // Гарантируется, что после вызова данной функции больше не будет
    // обучающих примеров.
    virtual void FinishTraining() = 0;
    
    // Добавление очередного тестового примера. Гарантируется, что эта функция
    // будет вызвана после FinishTraining().
    virtual void AddTestSession(const Session& session) = 0;
    
    // Получение результатов работы классификатора.
    virtual vector<int> FinishTesting() = 0;
    
    
public:
    Classifier() { }
    void TrainOn(const MarkedData& data);
    vector<int> TestOn(const UnmarkedData& data);

    // Удаление классификатора.
    virtual ~Classifier() { }

};

#endif /* defined(__Mathematica__classifier__) */
