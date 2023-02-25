#include "Logger.h"
#define MSP_NO_FILE
#define MSP_NO_THREAD

typedef struct Logger {
    FILE* file;
    //For writing
    char func[255];
    char fileDesc[255];
    va_list list;
    int line;
    LoggerType type;
    char msg[255];
    //For thread
#ifndef MSP_NO_THREAD
    pthread_mutex_t mutex;
    sem_t semFull;
    sem_t semEmpty;
#endif
    bool open;
}Logger;
Logger* logger;
void logger_print();

void logger_init(const char* filename) {
    logger = malloc(sizeof(Logger));
    if(logger == NULL) {
        FERROR("Failed to initialize logger.");
        return;
    }
    logger->file = fopen(filename, "w" );
    if(logger->file == NULL) {
        FERROR("Failed to open logger file.");
        free(logger);
        logger = NULL;
        return;
    }
    /*
     *  Multithreathing init
     */
#ifndef MSP_NO_THREAD
    sem_init(&logger->semEmpty, 0, 0);
    sem_init(&logger->semFull, 0, 1);
    pthread_mutex_init(&logger->mutex, NULL);
#endif
    /*
     * Write file desc like name time version authors etc.
     */
    fprintf(logger->file, "AUTHOMATED CREATED LOGGER FILE\n");
    fprintf(logger->file, "Program created by: ");
    fprintf(logger->file, AUTHOR);
    fprintf(logger->file, "\n");
    fprintf(logger->file, "Program: ");
    fprintf(logger->file, NAME);
    fprintf(logger->file, "\n");
    fprintf(logger->file, "Version: ");
    fprintf(logger->file, VERSION);
    fprintf(logger->file, "\n");
    fprintf(logger->file, "Created: %s %s\n\n", __DATE__, __TIME__);


    logger->open = true;
}

void logger_close() {
    logger->open = false;
#ifndef MSP_NO_THREAD
    sem_post(&logger->semEmpty);
#else
    logger_destroy();
#endif
}
void logger_destroy() {
    if(logger == NULL) {
        return;
    }
    if(logger->file != NULL)
        fclose(logger->file);
#ifndef MSP_NO_THREAD
    sem_destroy(&logger->semFull);
    sem_destroy(&logger->semEmpty);
    pthread_mutex_destroy(&logger->mutex);
#endif
    free(logger);
    logger = NULL;
}

void logger_log(LoggerType logType, const char* file, const char* func, int line, ...) {
    if(logger == NULL) {
        fprintf(stderr, "Logger is not initialized, call first logger_init()\n");
        return;
    }
    va_list list;
#ifndef MSP_NO_THREAD
    sem_wait(&logger->semFull);
    pthread_mutex_lock(&logger->mutex);
#endif
    // COPING TO LOGGER STRUCT MUST BE IN MUTEX AND SEMAPHORE

    va_start(list, line);
    char* m = va_arg(list, char*);
    va_copy(logger->list, list);
    va_end(list);
    strcpy(logger->fileDesc, file);
    strcpy(logger->func, func);
    strcpy(logger->msg, m);
    logger->line = line;
    logger->type = logType;
#ifndef MSP_NO_THREAD
    pthread_mutex_unlock(&logger->mutex);
    sem_post(&logger->semEmpty);
#else
    logger_print();
#endif

}

void logger_print() {
    va_list copyOfLogger;
    va_copy(copyOfLogger, logger->list);
    switch (logger->type) {
        case DEBUG:
            fprintf(logger->file, "[DEBUG] ");
            break;
        case INFO:
            fprintf(logger->file, "[INFO] ");
            break;
        case ERROR:
            fprintf(logger->file, "[ERROR] ");
            fprintf(stderr, "[ERROR] %s %s %d:", logger->fileDesc, logger->func, logger->line);
            vfprintf(stderr, logger->msg, copyOfLogger);
            fprintf(stderr, "\n");
            break;
        case WARNING:
            fprintf(logger->file, "[WARNING] ");
            break;
        case FATAL:
            fprintf(logger->file, "[FATAL] ");
            fprintf(stderr, "[FATAL ] %s %s %d:", logger->fileDesc, logger->func, logger->line);
            vfprintf(stderr, logger->msg, copyOfLogger);
            fprintf(stderr, "\n");
            break;
    }
    fprintf(logger->file, "%s %s ", __DATE__, __TIME__);
#ifndef MSP_NO_FILE
    fprintf(logger->file, "%s ", logger->fileDesc);
#endif //MSP_NO_FILE
    fprintf(logger->file, "%s ", logger->func);
    fprintf(logger->file, "%d ", logger->line);
    vfprintf(logger->file, logger->msg, logger->list);
    fprintf(logger->file, "\n");
    va_end(copyOfLogger);
}
#ifndef MSP_NO_THREAD
void* logger_thread(void* arg) {
    while(1) {
        sem_wait(&logger->semEmpty);
        if(!logger->open) {
            break;
        }
        pthread_mutex_lock(&logger->mutex);
        logger_print();
        pthread_mutex_unlock(&logger->mutex);
        sem_post(&logger->semFull);
    }
    logger_destroy();
    return NULL;
}
#endif