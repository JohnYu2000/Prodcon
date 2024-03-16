#ifndef EVENT_H
#define EVENT_H

enum EventType {
    ASK,  // Consumer waits for work
    RECEIVE,  // Consumer gets assigned work
    WORK,  // Producer receives a transaction from input
    SLEEP,  // Producer receive a sleep from input
    COMPLETE,  // Consumer completes assigned work
    END  // Producer reaches an EOF from input
};

#endif