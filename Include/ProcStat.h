//
// Created by piotrmiszta on 24.02.23.
//

#ifndef PROCESSES_PROCSTAT_H
#define PROCESSES_PROCSTAT_H
#include "Logger.h"
#define uint unsigned int
#define ulint unsigned long int
//https://www.baeldung.com/linux/total-process-cpu-usage TODO for calculate % usage CPU

//all from proc/[pid]/stat https://man7.org/linux/man-pages/man5/proc.5.html
typedef struct ProcStat {
    int pid;
    char* comm;
    char status;
    int ppid;
    int pgrp;
    int session;
    int tty_nr;
    int tpgid;
    uint flags;
    ulint minflt;
    ulint cminflt;
    ulint majflt;
    ulint cmajflt;
    ulint utime;
    ulint stime;
    long int cutime;
    long int cstime;
    long int priority;
    long int nice;
    long int num_threads;
    long int itrealvalue;
    long long unsigned int starttime;
    ulint vsize;
    long int rss;
    ulint rsslim;
    ulint startcode;
    ulint endcode;
    ulint startstack;
    ulint kstkesp;
    ulint kstkeip;
    ulint singal;
    ulint blocked;
    ulint sigignore;
    ulint sigcatch;
    ulint wchan;
    ulint nswap;
    ulint cnswap;
    int exit_signal;
    int proccessor;
    unsigned int rt_priority;
    uint policy;
    unsigned long long delayacct_blkio_ticks;
    ulint guest_time;
    long int cguest_time;

}ProcStat;


//Containg all stats for proccess
typedef struct ProcInfo {
    unsigned int pid;
    char* owner;
    char* group;
    char* cmdLine;

    unsigned long int uTime;
    unsigned long int sTime;
/*
 * https://stackoverflow.com/questions/39066998/what-are-the-meaning-of-values-at-proc-pid-stat
 */

}ProcInfo;



#endif //PROCESSES_PROCSTAT_H
