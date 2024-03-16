#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex {
    pthread_mutex_t queue_lock;
    pthread_mutex_t output_lock;
    pthread_cond_t queue_empty_cond;
    pthread_cond_t queue_full_cond;

    public:
        Mutex();
        pthread_mutex_t * getQueueLock();
        pthread_mutex_t * getOutputLock();
        pthread_cond_t * getQueueEmptyCond();
        pthread_cond_t * getQueueFullCond();
};

#endif