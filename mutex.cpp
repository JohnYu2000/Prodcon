/*
    This class stores all the mutex and condition variables to be used to achieve
    mutual exclusion between the producer and consumers
*/

#include "mutex.h"

Mutex::Mutex() {
    this->queue_lock = PTHREAD_MUTEX_INITIALIZER;
    this->output_lock = PTHREAD_MUTEX_INITIALIZER;
    this->queue_empty_cond = PTHREAD_COND_INITIALIZER;
    this->queue_full_cond = PTHREAD_COND_INITIALIZER;
}

pthread_mutex_t * Mutex::getQueueLock() {
    return &(this->queue_lock);
}

pthread_mutex_t * Mutex::getOutputLock() {
    return &(this->output_lock);
}

pthread_cond_t * Mutex::getQueueEmptyCond() {
    return &(this->queue_empty_cond);
}

pthread_cond_t * Mutex::getQueueFullCond() {
    return &(this->queue_full_cond);
}