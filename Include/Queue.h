//
// Created by piotrmiszta on 22.02.23.
//

#ifndef PROCESSES_QUEUE_H
#define PROCESSES_QUEUE_H
#include <stdlib.h>

typedef struct Queue Queue;

Queue* queue_create();
void queue_push_back(Queue* que, void* data);
void* queue_pop_first(Queue* que);
void queue_destroy(Queue* que);

#endif //PROCESSES_QUEUE_H
