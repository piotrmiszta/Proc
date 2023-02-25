#ifndef LOGGER_H
#define LOGGER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
typedef enum LoggerType {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
}LoggerType;

void logger_init(const char* filename);
void logger_destroy();
void logger_log(LoggerType logType, const char* file, const char* func, int line, ...);
void* logger_thread(void* arg);
void logger_close();
#define FERROR(msg)         fprintf(stderr, "[ERROR] %s %s %d: %s", __FILE__, __FUNCTION__, __LINE__, msg)
#define FFATAL(msg)         fprintf(stderr, "[FATAL] %s %s %d: %s", __FILE__, __FUNCTION__, __LINE__, msg)
//todo

#define LOG_DEBUG(...)      logger_log(DEBUG, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...)      logger_log(FATAL, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...)      logger_log(ERROR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...)    logger_log(WARNING, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)       logger_log(INFO, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)



#define AUTHOR      ("Piotr Miszta")
#define VERSION     ("1.0")
#define NAME        ("Processes")
#endif //LOGGER_H