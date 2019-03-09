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
                int maxEatingTimeInMilliseconds, std::shared_ptr<Logger> logger);
    void startDinner();
    void endDinner();

private:
    std::vector<Philosopher> philosophers;
    std::vector<std::thread> threads;
    const std::shared_ptr<Logger> logger;
    unsigned long numberOfPhilosophers;
    std::shared_ptr<std::atomic_bool> dinnerIsRunning;
    const int maxThinkingTimeInMilliseconds;
    const int maxEatingTimeInMilliseconds;
};


#endif //PHILOSOPHERS_DININGTABLE_H
