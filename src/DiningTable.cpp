//
// Created by tobias on 3/9/19.
//

#include "DiningTable.h"

DiningTable::DiningTable(unsigned long numberOfPhilosophers, const int maxThinkingTimeInMilliseconds,
                         const int maxEatingTimeInMilliseconds, const bool withDeadlock,
                         const std::shared_ptr<Logger> logger) :
        numberOfPhilosophers(numberOfPhilosophers),
        maxThinkingTimeInMilliseconds(maxThinkingTimeInMilliseconds),
        maxEatingTimeInMilliseconds(maxEatingTimeInMilliseconds),
        withDeadlock(withDeadlock),
        logger(logger),
        threads(std::vector<std::thread>()),
        philosophers(std::vector<Philosopher>()),
        dinnerIsRunning(std::make_shared<std::atomic_bool>(false)) {

    auto forks = std::vector<std::shared_ptr<Fork>>();
    for (unsigned long i = 0; i < numberOfPhilosophers; ++i) {
        forks.emplace_back(std::make_shared<Fork>(i));
    }
    auto randomIntGenerator = std::make_shared<RandomIntGenerator>();
    for (unsigned long j = 0; j < numberOfPhilosophers; ++j) {
        philosophers.emplace_back(Philosopher(j,
                                              maxThinkingTimeInMilliseconds,
                                              maxEatingTimeInMilliseconds,
                                              withDeadlock,
                                              forks[(j + 1) % numberOfPhilosophers],
                                              forks[j],
                                              dinnerIsRunning,
                                              randomIntGenerator,
                                              logger));
    }

}

void DiningTable::startDinner() {
    for (auto &philosopher : philosophers) {
        threads.emplace_back(std::thread([&philosopher]() {
            philosopher.dine();
        }));
    }
    dinnerIsRunning->store(true);
}

void DiningTable::endDinner() {
    dinnerIsRunning->store(false);
    for (auto &thread : threads) {
        thread.join();
    }
}

