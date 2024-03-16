#include "producer.h"
#include "consumer.h"

#include <iostream>

using namespace std;

vector<Consumer*> consumerVector;

int main(int argc, char** argv) {
    int nthreads;
    int log = 0;
    if (argc == 2) {
        nthreads = atoi(argv[1]);
    } else if (argc >= 3) {
        nthreads = atoi(argv[1]);
        log = atoi(argv[2]);
    } else {
        printf("Not enough inputs!\n");
        return 0;
    }


    char output_name[sizeof("prodcon.%d.log") + 1];
    if (log == 0) {
        sprintf(output_name, "prodcon.log");
    } else if (log > 0) {
        sprintf(output_name, "prodcon.%d.log", log);
    }

    // Initialize mutexes
    Mutex * mutex = new Mutex();

    // Initialize work queue
    WorkQueue * tasks = new WorkQueue();

    // Initialize the logger
    Logger * logger = new Logger(output_name, mutex, tasks);

    // Initialize the producer
    Producer prod = Producer(nthreads, logger, tasks, mutex);

    // Initialize the consumers
    for (int i = 0; i < nthreads; i++) {
        consumerVector.push_back(new Consumer(i + 1, logger, tasks, mutex));
    }

    // Run the producer
    while (prod.run());

    // Cleanup consumers
    pthread_mutex_lock(mutex->getQueueLock());
    for (Consumer* consumer: consumerVector) {
        consumer->setEnding(true);
    }
    pthread_cond_broadcast(mutex->getQueueEmptyCond());
    pthread_mutex_unlock(mutex->getQueueLock());

    // Wait for consumers to close
    for (Consumer * consumer: consumerVector) {
        pthread_join(consumer->getThreadId(), NULL);
    }

    // Displays the summery statistics
    /*
        I created statVector to store the information that I need to output to the summary log.
        I didn't directly provide consumerVector as my input because I had issues when I
        included consumer.h into logger.h. I already included logger.h in consumer.h so I
        believe the problem is recursive definitions.
    */
    vector<tuple<int, int>> statVector;
    for (Consumer* consumer: consumerVector) {
        statVector.push_back(make_tuple(consumer->getId(), consumer->getTasksComplete()));
        delete consumer;
    }
    logger->Summary(statVector);

    consumerVector.clear();

    delete mutex;
    delete tasks;
    delete logger;

    return 0;
}