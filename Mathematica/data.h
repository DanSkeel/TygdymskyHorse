//
//  data.h
//  Mathematica
//
//  Created by Akim on 11/19/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#ifndef __Mathematica__data__
#define __Mathematica__data__

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

struct FileData {
    string file_name;
    FileData(const string& file_name) {
        this->file_name = "/Users/akim/Desktop/Mathematica/Mathematica/dataset/" + file_name;
    }
    void Dispose();
};

struct MarkedData : FileData {
    MarkedData(const string& file_name) :
    FileData(file_name) { }
};

struct UnmarkedData : FileData {
    UnmarkedData(const string& file_name) :
    FileData(file_name) { }
};

struct TrainingSet {
    // Имя файла, в котором содержится обучающая выборка.
    MarkedData train_data;
    
    // Имя файла, в котором содержится тестовая выборка. Из тестовой выборки будет
    // удалена вся информация о переходах в другие поисковые системы.
    UnmarkedData test_data;
    
    // Имя файла, в котором содержится тестовая выборка до удаления информации о
    // переходах. Служит для оценки качества алгоритмов.
    MarkedData test_results_data;
    
    TrainingSet(const string& set_name);
    void Dispose();
};

struct LogEntry {
    int time_passed;
    char record_type;
    virtual ~LogEntry() { }
};

struct Query : LogEntry {
    int query_id;
    int serp_id;
    vector<int> list_of_urls;
    virtual ~Query() {
    }
};

struct Click : LogEntry {
    int serp_id;
    int url_id;
};

struct Switch : LogEntry {
};

struct Session {
    int session_id;
    int day_id;
    int user_id;
    char switch_type;
    vector<LogEntry*> session_log;
    
    bool HasSwitches();
    ~Session();
};

#endif /* defined(__Mathematica__data__) */
