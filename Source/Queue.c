//
// Created by piotrmiszta on 22.02.23.
//
#include "Queue.h"

typedef struct Node {
    struct Node* next;
    void* data;
}Node;

typedef struct Queue {
    Node* head;
}Queue;

Queue* queue_create() {
    Queue* que = malloc(sizeof (Queue));
    if(que == NULL) {

    }
}
void queue_push_back(Queue* que, void* data) {

}
void* queue_pop_first(Queue* que) {

}
void queue_destroy(Queue* que) {

}
