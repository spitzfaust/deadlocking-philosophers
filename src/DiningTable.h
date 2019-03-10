//
// Created by tobias on 3/9/19.
//

#ifndef PHILOSOPHERS_DININGTABLE_H
#define PHILOSOPHERS_DININGTABLE_H


#include "Logger.h"
#include "Philosopher.h"

class DiningTable {
public:
    DiningTable(unsigned long numberOfPhilosophers, int maxThinkingTimeInMilliseconds,
                int maxEatingTimeInMilliseconds, const bool withDeadlock,
                std::shared_ptr<Logger> logger);

    void startDinner();

    void endDinner();

private:
    std::vector<Philosopher> philosophers;
    std::vector<std::thread> threads;
    const std::shared_ptr<Logger> logger;
    std::shared_ptr<std::atomic_ullong> forkWaitTimeMilliseconds;
    std::shared_ptr<std::atomic_bool> dinnerIsRunning;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    unsigned long numberOfPhilosophers;
    const int maxThinkingTimeInMilliseconds;
    const int maxEatingTimeInMilliseconds;
    const bool withDeadlock;
};


#endif //PHILOSOPHERS_DININGTABLE_H
