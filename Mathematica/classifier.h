//
//  classifier.h
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef Mathematica_classifier_h
#define Mathematica_classifier_h

#include <vector>
#include "data.h"
using std::vector;

class Classifier {
public:
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
    
    // Удаление классификатора.
    virtual ~Classifier() { }
};

#endif
