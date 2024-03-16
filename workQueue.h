#ifndef WORKQUEUE_H
#define WORKQUEUE_H

#include "command.h"

#include <queue>

class WorkQueue {
    std::queue<Command> tasks;

    public:
        WorkQueue();
        std::queue<Command> * getQueue();
        int getQueueSize();
};

#endif