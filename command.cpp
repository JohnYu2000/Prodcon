/*
    This file is responsible for retrieving commands from input and storing that information.
    In Summary: This file handles all prodcon inputs
*/

#include "command.h"

using namespace std;

Command::Command() {
    this->n = 0;
    this->et = SLEEP;
}

Command::Command(int n, EventType event) {
    this->n = n;
    this->et = event;
}

EventType Command::getEventType() {
    return this->et;
}

int Command::getN() {
    return this->n;
}

/*
    This method gets the next input from terminal or file
*/
void Command::getNextCommand() {
    char cmdChar;
    int cmdParam;
    bool eof = (scanf(" %c%d", &cmdChar, &cmdParam) == -1);

    if (eof) {
        this->n = 0;
        this->et = END;
    } else {
        this->n = cmdParam;
        switch (cmdChar) {
            case 'T':
                this->et = WORK;
                break;
            case 'S':
                this->et = SLEEP;
                break;
            default:
                break;
        }
    }
}