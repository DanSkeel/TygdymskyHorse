//
//  output_writer.cpp
//  Mathematica
//
//  Created by Akim on 11/20/12.
//  Copyright (c) 2012 Akim. All rights reserved.
//

#include <cassert>
#include "output_writer.h"

OutputWriter::OutputWriter(const MarkedData& data) {
    file_name = data.file_name;
    fout = fopen(data.file_name.c_str(), "wb");
    is_marked = true;
}

OutputWriter::OutputWriter(const UnmarkedData& data) {
    file_name = data.file_name;
    fout = fopen(data.file_name.c_str(), "wb");
    is_marked = false;
}

string OutputWriter::GetFileName() const {
    return file_name;
}

void OutputWriter::Print(const Session &session) {
    fprintf(fout, "%d\t%d\t%c\t%d", session.session_id,
            session.day_id, 'M', session.user_id);
    if (is_marked) {
        fprintf(fout, "\t%c", session.switch_type);
    }
    fprintf(fout, "\n");
    for (size_t i = 0; i < session.session_log.size(); ++i) {
        LogEntry* log_entry = session.session_log[i];
        if (log_entry->record_type == 'S' && !is_marked) {
            // Do not print click info in unmarked output.
            continue;
        }
        fprintf(fout, "%d\t%d\t%c", session.session_id, log_entry->time_passed, log_entry->record_type);
        if (log_entry->record_type == 'Q') {
            fprintf(fout, "\t%d\t%d", ((Query*)log_entry)->serp_id, ((Query*)log_entry)->query_id);
            vector<int>& urls = ((Query*)log_entry)->list_of_urls;
            for (size_t j = 0; j < urls.size(); ++j) {
                fprintf(fout, "\t%d", urls[j]);
            }
        } else if (log_entry->record_type == 'C') {
            fprintf(fout, "\t%d\t%d", ((Click*)log_entry)->serp_id, ((Click*)log_entry)->url_id);
        } else if (log_entry->record_type == 'S') {
            assert(is_marked);
            // Do nothing
        } else assert(false);
        fprintf(fout, "\n");
    }
}

void OutputWriter::Close() {
    fclose(fout);
}