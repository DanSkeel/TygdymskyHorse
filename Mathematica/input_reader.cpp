//
//  input_reader.cpp
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include <cassert>
#include <sstream>
#include "input_reader.h"
#include "logger.h"
#include "utils.h"

const double InputReader::LOG_EVERY = 0.10;

void InputReader::GetNextLine() {
    has_next = fgets(next_line, MAX_LINE_LEN, fin) != NULL;
    pos_in_line = 0;
    while (next_line[pos_in_line] == '\t' || next_line[pos_in_line] == ' ') {
        ++pos_in_line;
    }
    size_t l = strlen(next_line);
    if (l > 0 && next_line[l - 1] == '\n') {
        next_line[l - 1] = 0;
    }
    chars_read += l;
    while (file_size * next_log < chars_read) {
        std::ostringstream message;
        message << "Read " << (double)chars_read * 100.0 / file_size << "%";
        Logger::Info(message.str());
        next_log += LOG_EVERY;
    }
}

InputReader::InputReader(const MarkedData& data) {
    is_marked = true;
    fin = fopen(data.file_name.c_str(), "rb");
    file_size = Utils::GetFileSize(data.file_name);
    chars_read = 0;
    next_log = LOG_EVERY;
    GetNextLine();
    Logger::Info("Reading " + data.file_name);
}

InputReader::InputReader(const UnmarkedData& data) {
    is_marked = false;
    fin = fopen(data.file_name.c_str(), "rb");
    file_size = Utils::GetFileSize(data.file_name);
    chars_read = 0;
    next_log = LOG_EVERY;
    GetNextLine();
    Logger::Info("Reading " + data.file_name);
}

int InputReader::GetNextInt() {
    assert(HasNextTokenInString());
    int ans = 0;
    while (next_line[pos_in_line] != '\t' && next_line[pos_in_line] != ' ' && next_line[pos_in_line] != 0) {
        assert(next_line[pos_in_line] >= '0' && next_line[pos_in_line <= '9']);
        ans = ans * 10 + next_line[pos_in_line] - '0';
        ++pos_in_line;
    }
    while (next_line[pos_in_line] == '\t' || next_line[pos_in_line] == ' ') {
        ++pos_in_line;
    }
    return ans;
}

char InputReader::GetNextChar() {
    assert(HasNextTokenInString());
    char ans = next_line[pos_in_line++];
    while (next_line[pos_in_line] == '\t' || next_line[pos_in_line] == ' ') {
        ++pos_in_line;
    }
    return ans;
}

bool InputReader::HasNextTokenInString() {
    return next_line[pos_in_line] != 0;
}

Session* InputReader::GetNextSession() {
    Session* session = new Session();
    // has_next should contain metadata info;
    session->session_id = GetNextInt();
    session->day_id = GetNextInt();
    char record_type = GetNextChar();
    assert(record_type == 'M');
    session->user_id = GetNextInt();
    if (is_marked) {
        session->switch_type = GetNextChar();
    } else {
        session->switch_type = '?';
    }
    assert(!HasNextTokenInString());
    while (true) {
        GetNextLine();
        if (!has_next) {
            // end of file.
            break;
        }
        int cur_session_id = GetNextInt();
        if (cur_session_id != session->session_id) {
            // next session
            pos_in_line = 0;
            while (next_line[pos_in_line] == '\t' || next_line[pos_in_line] == ' ') {
                ++pos_in_line;
            }
            break;
        }
        int time_passed = GetNextInt();
        char record_type = GetNextChar();
        LogEntry* log_entry;
        if (record_type == 'Q') {
            log_entry = new Query();
            ((Query*)log_entry)->serp_id = GetNextInt();
            ((Query*)log_entry)->query_id = GetNextInt();
            while (HasNextTokenInString()) {
                int url_id = GetNextInt();
                ((Query*)log_entry)->list_of_urls.push_back(url_id);
            }
        } else if (record_type == 'C') {
            log_entry = new Click();
            ((Click*)log_entry)->serp_id = GetNextInt();
            ((Click*)log_entry)->url_id = GetNextInt();
        } else if (record_type == 'S') {
            log_entry = new Switch();
        }
        assert(!HasNextTokenInString());
        log_entry->time_passed = time_passed;
        log_entry->record_type = record_type;
        session->session_log.push_back(log_entry);
    }
    
    return session;
}