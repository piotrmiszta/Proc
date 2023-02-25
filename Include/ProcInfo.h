//
// Created by piotrmiszta on 25.02.23.
//

#ifndef PROCESSES_PROCINFO_H
#define PROCESSES_PROCINFO_H
#include "ProcStat.h"

typedef struct ProcInfo {
    unsigned int pid;
    char* owner;
    char* group;
    ProcStat* stats;

/*
 * https://stackoverflow.com/questions/39066998/what-are-the-meaning-of-values-at-proc-pid-stat
 */

}ProcInfo;

#endif //PROCESSES_PROCINFO_H
