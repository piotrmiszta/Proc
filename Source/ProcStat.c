//
// Created by piotrmiszta on 25.02.23.
//
#include "ProcStat.h"
#define uint unsigned int
#define ulint unsigned long int
//https://www.baeldung.com/linux/total-process-cpu-usage TODO for calculate % usage CPU

//all from proc/[pid]/stat https://man7.org/linux/man-pages/man5/proc.5.html
void procStat_read(ProcStat* proc, FILE* file);

typedef struct ProcStat {
    int pid;                                    //PID
    char comm[255];                                 //COMM
    char status;                                //R, S, D , Z
    int ppid;                                   //Parent PID
    int pgrp;                                   //Process group id
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
    ulint start_data;
    ulint end_data;
    ulint start_brk;
    ulint arg_start;
    ulint arg_end;
    ulint env_start;
    ulint env_end;
    int exit_code;
} ProcStat;

ProcStat* procStat_create(int pid) {
    /*
     * First open file, if cant return nullptr else read data
     */
    ProcStat* procStat;
    FILE* file;
    // CREATING STRING LIKE /proc/<pid>/stat
    char fileStat[6] = "/stat";  //       /stat0 -- size = 6
    char stringPid[7];           //        size = 7
    char filename[20] = "/proc/";          //size = 7 so all have max 20 size
    sprintf(stringPid, "%d", pid);
    strcat(filename, stringPid);
    strcat(filename, fileStat);

    file = fopen(filename, "r");
    if(file == NULL) {
        LOG_ERROR("Cant open file %s", filename);
        return NULL;
    }
    procStat = malloc(sizeof(ProcStat));
    if(procStat == NULL) {
        LOG_ERROR("Cant allocate memory for procStat");
        fclose(file);
        return NULL;
    }
    procStat_read(procStat, file);
    return procStat;
}

void procStat_read(ProcStat* proc, FILE* file) {
    fscanf(file, "%d ", &proc->pid);
    fscanf(file, "%s ", proc->comm);
    fscanf(file, "%c ", &proc->status);
    fscanf(file, "%d", &proc->ppid);
    fscanf(file, "%d", &proc->pgrp);
    fscanf(file, "%d", &proc->session);
    fscanf(file, "%d", &proc->tty_nr);
    fscanf(file, "%d", &proc->tpgid);
    fscanf(file, "%u", &proc->flags);
    fscanf(file, "%lu", &proc->minflt);
    fscanf(file, "%lu", &proc->cminflt);
    fscanf(file, "%lu", &proc->majflt);
    fscanf(file, "%lu", &proc->cmajflt);
    fscanf(file, "%lu", &proc->utime);
    fscanf(file, "%lu", &proc->stime);
    fscanf(file, "%ld", &proc->cutime);
    fscanf(file, "%ld", &proc->cstime);
    fscanf(file, "%ld", &proc->priority);
    fscanf(file, "%ld", &proc->nice);
    fscanf(file, "%ld", &proc->num_threads);
    fscanf(file, "%ld", &proc->itrealvalue);
    fscanf(file, "%llu", &proc->starttime);
    fscanf(file, "%lu", &proc->vsize);
    fscanf(file, "%ld", &proc->rss);
    fscanf(file, "%lu", &proc->rsslim);
    fscanf(file, "%lu", &proc->startcode);
    fscanf(file, "%lu", &proc->endcode);
    fscanf(file, "%lu", &proc->startstack);
    fscanf(file, "%lu", &proc->kstkesp);
    fscanf(file, "%lu", &proc->kstkeip);
    fscanf(file, "%lu", &proc->singal);
    fscanf(file, "%lu", &proc->blocked);
    fscanf(file, "%lu", &proc->sigignore);
    fscanf(file, "%lu", &proc->sigcatch);
    fscanf(file, "%lu", &proc->wchan);
    fscanf(file, "%lu", &proc->nswap);
    fscanf(file, "%lu", &proc->cnswap);
    fscanf(file, "%d", &proc->exit_signal);
    fscanf(file, "%d", &proc->proccessor);
    fscanf(file, "%u", &proc->rt_priority);
    fscanf(file, "%u", &proc->policy);
    fscanf(file, "%llu", &proc->delayacct_blkio_ticks);
    fscanf(file, "%lu", &proc->guest_time);
    fscanf(file, "%ld", &proc->cguest_time);
    fscanf(file, "%lu", &proc->start_data);
    fscanf(file, "%lu", &proc->end_data);
    fscanf(file, "%lu", &proc->start_brk);
    fscanf(file, "%lu", &proc->arg_start);
    fscanf(file, "%lu", &proc->arg_end);
    fscanf(file, "%lu", &proc->env_start);
    fscanf(file, "%lu", &proc->env_end);
    fscanf(file, "%d", &proc->exit_code);
}

void procStat_write(ProcStat* proc, FILE* file) {
    fprintf(file, "%d\t", proc->pid);
    fprintf(file, "%s\t", proc->comm);
    fprintf(file, "%c\t", proc->status);
    fprintf(file, "%d\t", proc->ppid);
    fprintf(file, "%d\t", proc->pgrp);
    fprintf(file, "%d\t", proc->session);
    fprintf(file, "%d\t", proc->tty_nr);
    fprintf(file, "%d\t", proc->tpgid);
    fprintf(file, "%u\t", proc->flags);
    fprintf(file, "%lu\t", proc->minflt);
    fprintf(file, "%lu\t", proc->cminflt);
    fprintf(file, "%lu\t", proc->majflt);
    fprintf(file, "%lu\t", proc->cmajflt);
    fprintf(file, "%lu\t", proc->utime);
    fprintf(file, "%lu\t", proc->stime);
    fprintf(file, "%ld\t", proc->cutime);
    fprintf(file, "%ld\t", proc->cstime);
    fprintf(file, "%ld\t", proc->priority);
    fprintf(file, "%ld\t", proc->nice);
    fprintf(file, "%ld\t", proc->num_threads);
    fprintf(file, "%ld\t", proc->itrealvalue);
    fprintf(file, "%llu\t", proc->starttime);
    fprintf(file, "%lu\t", proc->vsize);
    fprintf(file, "%ld\t", proc->rss);
    fprintf(file, "%lu\t", proc->rsslim);
    fprintf(file, "%lu\t", proc->startcode);
    fprintf(file, "%lu\t", proc->endcode);
    fprintf(file, "%lu\t", proc->startstack);
    fprintf(file, "%lu\t", proc->kstkesp);
    fprintf(file, "%lu\t", proc->kstkeip);
    fprintf(file, "%lu\t", proc->singal);
    fprintf(file, "%lu\t", proc->blocked);
    fprintf(file, "%lu\t", proc->sigignore);
    fprintf(file, "%lu\t", proc->sigcatch);
    fprintf(file, "%lu\t", proc->wchan);
    fprintf(file, "%lu\t", proc->nswap);
    fprintf(file, "%lu\t", proc->cnswap);
    fprintf(file, "%d\t", proc->exit_signal);
    fprintf(file, "%d\t", proc->proccessor);
    fprintf(file, "%u\t", proc->rt_priority);
    fprintf(file, "%u\t", proc->policy);
    fprintf(file, "%llu\t", proc->delayacct_blkio_ticks);
    fprintf(file, "%lu\t", proc->guest_time);
    fprintf(file, "%ld\t", proc->cguest_time);
    fprintf(file, "%lu\t", proc->start_data);
    fprintf(file, "%lu\t", proc->end_data);
    fprintf(file, "%lu\t", proc->start_brk);
    fprintf(file, "%lu\t", proc->arg_start);
    fprintf(file, "%lu\t", proc->arg_end);
    fprintf(file, "%lu\t", proc->env_start);
    fprintf(file, "%lu\t", proc->env_end);
    fprintf(file, "%d\t", proc->exit_code);
}

double procStat_percent(ProcStat* proc) {
    FILE * file = fopen("/proc/uptime", "r");
    double uptime;
    fscanf(file, "%lf", &uptime);
    double total_time = proc->utime + proc->stime;
    total_time = total_time+proc->cutime + proc->cstime;
    double sec = uptime - (proc->starttime/CLOCKS_PER_SEC);
    double usage_sec = 100* ((total_time/CLOCKS_PER_SEC)/sec);
    return usage_sec;

}