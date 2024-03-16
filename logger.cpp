/*
    This file handles all methods that deal with logging to the output file
    In Summary: This file handles all prodcon outputs
*/

#include "logger.h"

using namespace std;
using namespace chrono;

/*
    Constructor for the Logger Class

    Params:
        - output_name: This is a char* to the name of the output file
        - mutex: This is a class containing the mutex locks and conditions
        - tasks: This class is the queue containing work provided by the user
*/
Logger::Logger(char * output_name, Mutex * mutex, WorkQueue * tasks) {
    this->output_name = output_name;
    this->output_file = fopen(this->output_name, "w");
    this->start_time = high_resolution_clock::now();
    this->curr_time = high_resolution_clock::now();
    this->mutex = mutex;
    this->tasks = tasks;
}

Logger::~Logger() {
    fclose(this->output_file);
}

string Logger::getEventTypeAsString(EventType et) {
    switch (et) {
        case ASK:
            return "Ask";
        case RECEIVE:
            return "Receive";
        case WORK:
            return "Work";
        case SLEEP:
            return "Sleep";
        case COMPLETE:
            return "Complete";
        case END:
            return "End";
        default:
            return "";
    };
}

/*
    This method logs the event to the output file
*/
void Logger::Log(int id, EventType et, Command * cmd) {
    // Get the execution time of the program
    this->curr_time = high_resolution_clock::now();
    double duration = duration_cast<microseconds>(curr_time - start_time).count() / (double)1000000;

    // Producer/consumer id is obtained from the input parameter

    // Event type is obtained from the input parameter cmd
    char et_str[] = "          ";
    sprintf(et_str, "%s", this->getEventTypeAsString(et).c_str());

    // Q (number of transactions) is obtained from the input parameter
    char queueSize[] = "    ";
    if (et == RECEIVE || et == WORK) {
        int q = this->tasks->getQueueSize();
        sprintf(queueSize, "Q=%2d", q);
    }

    // The parameter that was given for T or s is obtained from the input parameter cmd
    char n_str[] = "    ";
    if (cmd != nullptr) {
        sprintf(n_str, "%4u", cmd->getN());
    }

    // Log to the output file
    pthread_mutex_lock(this->mutex->getOutputLock());
    fprintf(this->output_file, "%7.3f ID=%2u %4s %-10s %5s\n", duration, id, queueSize, et_str, n_str);
    pthread_mutex_unlock(this->mutex->getOutputLock());

    switch (et) {
        case ASK:
            this->askCnt += 1;
            break;
        case RECEIVE:
            this->receiveCnt += 1;
            break;
        case WORK:
            this->workCnt += 1;
            break;
        case SLEEP:
            this->sleepCnt += 1;
            break;
        case COMPLETE:
            this->completeCnt += 1;
            break;
        default:
            break;
    }
}

/*
    This method logs the summary statistics to the output file
*/
void Logger::Summary(vector<tuple<int, int>> consumerStats) {
    /*
        I decided not to wrap this method with a mutex because only main.cpp invokes this method.
    */
    fprintf(this->output_file, "Summary:\n");
    fprintf(this->output_file, "    %-12s %5d\n", "Work", this->workCnt);
    fprintf(this->output_file, "    %-12s %5d\n", "Ask", this->askCnt);
    fprintf(this->output_file, "    %-12s %5d\n", "Receive", this->receiveCnt);
    fprintf(this->output_file, "    %-12s %5d\n", "Complete", this->completeCnt);
    fprintf(this->output_file, "    %-12s %5d\n", "Sleep", this->sleepCnt);

    for (tuple<int, int> stat: consumerStats) {
        fprintf(this->output_file, "    Thread %-3d %7d\n", get<0>(stat), get<1>(stat));
    }

    this->curr_time = high_resolution_clock::now();
    double duration = duration_cast<microseconds>(curr_time - start_time).count() / (double)1000000;
    double transactions_per_second = this->completeCnt / duration;
    fprintf(this->output_file, "Transactions per second: %-5.2f", transactions_per_second);
}