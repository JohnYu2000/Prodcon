#ifndef CONSUMER_H
#define CONSUMER_H

#include "logger.h"
#include "workQueue.h"
#include "tands.h"

#include <pthread.h>

class Consumer {
    int id;
    pthread_t thread_id;
    bool ending;
    Logger * logger;
    WorkQueue * tasks;
    Mutex * mutex;
    int tasks_complete = 0;
    public:
        Consumer(int id, Logger * logger, WorkQueue * tasks, Mutex * mutex);
        void setEnding(bool arg);
        bool askForWork();
        pthread_t getThreadId();
        int getId();
        int getTasksComplete();
};

void * thread_function(void * args_p);

#endif