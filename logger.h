#ifndef LOGGER_INCLUDED
#define LOGGER_INCLUDED

#include "command.h"
#include "event.h"
#include "mutex.h"
#include "workQueue.h"

#include <chrono>
#include <stdio.h>
#include <pthread.h>
#include <vector>
#include <tuple>

class Logger {
    private:
        char * output_name;
        FILE * output_file;
        std::chrono::time_point<std::chrono::system_clock> start_time;
        std::chrono::time_point<std::chrono::system_clock> curr_time;
        int workCnt = 0;
        int askCnt = 0;
        int receiveCnt = 0;
        int completeCnt = 0;
        int sleepCnt = 0;
        Mutex * mutex;
        WorkQueue * tasks;
    public:
        Logger(char * output_name, Mutex * mutex, WorkQueue * tasks);
        ~Logger();
        std::string getEventTypeAsString(EventType et);
        void Log(int id, EventType et, Command * cmd);
        void Summary(std::vector<std::tuple<int, int>> consumerStats);
};

#endif