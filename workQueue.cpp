/*
    This class is the queue containing the jobs to be performed
    The producer adds jobs to this queue
    The consumer receives jobs from this queue
*/

#include "workQueue.h"

using namespace std;

WorkQueue::WorkQueue() {
    ;
}

queue<Command> * WorkQueue::getQueue() {
    return &(this->tasks);
}

int WorkQueue::getQueueSize() {
    return (this->tasks).size();
}