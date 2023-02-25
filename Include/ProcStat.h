//
// Created by piotrmiszta on 24.02.23.
//

#ifndef PROCESSES_PROCSTAT_H
#define PROCESSES_PROCSTAT_H
#include "Logger.h"
#include <stdio.h>

typedef struct ProcStat ProcStat;

ProcStat* procStat_create(int pid);
void procStat_write(ProcStat* proc, FILE* file);
double procStat_percent(ProcStat* proc);

#endif //PROCESSES_PROCSTAT_H
