#ifndef COMMAND_H
#define COMMAND_H

#include "event.h"
#include "tands.h"
#include <string>
#include <iostream>

class Command {
    int n;
    EventType et;  // Transaction or Sleep

    public:
        Command();
        Command(int n, EventType event);
        EventType getEventType();
        int getN();
        void getNextCommand();
};

#endif