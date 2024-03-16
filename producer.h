#ifndef PRODUCER_H
#define PRODUCER_H

#include "command.h"
#include "logger.h"
#include "workQueue.h"
#include "tands.h"

#include <iostream>
#include <queue>

class Producer {
    int maxQueueSize;
    Logger * logger;
    WorkQueue * tasks;
    Mutex * mutex;

    public:
        Producer(int nthread, Logger * logger, WorkQueue * tasks, Mutex * mutex);
        bool run();
        void transaction(Command * cmd);
        void sleep(Command * cmd);
        void close(Command * cmd);
};

#endif