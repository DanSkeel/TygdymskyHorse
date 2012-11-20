//
//  test_generator.h
//  Mathematica
//
//  Created by Akim on 11/19/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__test_generator__
#define __Mathematica__test_generator__

#include <iostream>
#include <string>
#include "data.h"
using std::string;

class TestGenerator {

public:
    /*
     Разделяет имеющуюся размеченную выборку на обучающую и тестовую.
     Служит для локального тестирования алгоритмов. Разделение ведётся по
     SessionId: некоторые сессии целиком попадают в обучающую выборку, а остальные -
     целиком в тестовую выборку.
     
     sample_data - исходная размеченная выборка.
     train_ratio - примерное отношение размеров обучающей и тестовой выборок.
     
     result - TrainingSample, содержащий информацию о названии файлов, полученных
     в результате разделения.
     */
    static TrainingSet SplitTest(const MarkedData& sample_data, double train_ratio);
    
    /*
     Создаёт подвыборку на основе имеющейся размеченной выборки. Разделение ведётся по 
     UserId: все сессии некоторых пользователей целиком попадают в подвыборку, а сессии
     остальных пользователей целиком исключаются из подвыборки.
     
     
     sample_data - исходная размеченная выборка.
     sample_ratio - примерное отношение размеров исходной и получившейся выборки.
     subtest_file_name - название файла, который будет содержать выборку.
     
     result - подвыборка меньшего размера, полученная на основе исходной выборки.
     */
    static MarkedData GenerateSubTest(const MarkedData& sample_data,
                                      double sample_ratio,
                                      const string& subtest_file_name);
    
    /*
     То же самое, но название файла выбирается случайно.
     */
    static MarkedData GenerateSubTest(const MarkedData& sample_data,
                                      double sample_ratio);
};

#endif /* defined(__Mathematica__test_generator__) */