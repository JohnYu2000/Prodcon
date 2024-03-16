/*
    This class handles all functionality for the consumers
*/

#include "consumer.h"

Consumer::Consumer(int id, Logger * logger, WorkQueue * tasks, Mutex * mutex) {
    this->id = id;
    this->ending = false;
    this->logger = logger;
    this->tasks = tasks;
    this->mutex = mutex;
    pthread_create(&thread_id, NULL, thread_function, this);
}

void Consumer::setEnding(bool arg) {
    this->ending = arg;
}

bool Consumer::askForWork() {
    Command command;
    this->logger->Log(this->id, ASK, nullptr);

    // Wait for work
    pthread_mutex_lock(this->mutex->getQueueLock());
    while (this->tasks->getQueue()->empty()) {
        if (this->ending) {
            pthread_mutex_unlock(this->mutex->getQueueLock());
            return false;
        }
        pthread_cond_wait(this->mutex->getQueueEmptyCond(), this->mutex->getQueueLock());
    }

    command = this->tasks->getQueue()->front();
    this->tasks->getQueue()->pop();

    pthread_cond_signal(this->mutex->getQueueFullCond());  // Signals to producer that queue is no longer full

    pthread_mutex_unlock(this->mutex->getQueueLock());

    this->logger->Log(this->id, RECEIVE, &command);

    Trans(command.getN());
    this->logger->Log(this->id, COMPLETE, &command);

    this->tasks_complete += 1;

    return true;
}

pthread_t Consumer::getThreadId() {
    return this->thread_id;
}

int Consumer::getId() {
    return this->id;
}

int Consumer::getTasksComplete() {
    return this->tasks_complete;
}

void * thread_function(void * args_p) {
    Consumer * consumer = (Consumer *) args_p;
    while (consumer->askForWork());
    return nullptr;
}