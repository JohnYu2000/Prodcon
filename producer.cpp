/*
    This class handles all functionality for the producer
*/

#include "producer.h"

using namespace std;

Producer::Producer(int nthread, Logger * logger, WorkQueue * tasks, Mutex * mutex) {
    this->maxQueueSize = nthread * 2;
    this->logger = logger;
    this->tasks = tasks;
    this->mutex = mutex;
}

bool Producer::run() {
    Command command = Command();
    command.getNextCommand();

    if (command.getEventType() == WORK) {
        this->transaction(&command);
    } else if (command.getEventType() == SLEEP) {
        this->sleep(&command);
    } else if (command.getEventType() == END) {
        this->close(&command);
        return false;
    }
    return true;
}

void Producer::transaction(Command * cmd) {
    this->logger->Log(0, WORK, cmd);

    // Add transaction to queue
    pthread_mutex_lock(this->mutex->getQueueLock());
    while (this->tasks->getQueueSize() >= this->maxQueueSize) {
        pthread_cond_wait(this->mutex->getQueueFullCond(), this->mutex->getQueueLock());
    }
    this->tasks->getQueue()->push(*(cmd));

    pthread_cond_signal(this->mutex->getQueueEmptyCond());  // Signal to a consumer that queue is no longer empty
    pthread_mutex_unlock(this->mutex->getQueueLock());
}

void Producer::sleep(Command * cmd) {
    this->logger->Log(0, SLEEP,cmd);

    Sleep(cmd->getN());
}

void Producer::close(Command * cmd) {
    this->logger->Log(0, END, cmd);
}