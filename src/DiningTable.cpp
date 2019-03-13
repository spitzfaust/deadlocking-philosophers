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
        forks(std::vector<std::shared_ptr<Fork>>()),
        dinnerIsRunning(std::make_shared<std::atomic_bool>(false)),
        forkWaitTimeMilliseconds(std::make_shared<std::atomic_ullong>(0)) {}

void DiningTable::startDinner() {
    for (unsigned long i = 0; i < numberOfPhilosophers; ++i) {
        forks.emplace_back(std::make_shared<Fork>(i, forkWaitTimeMilliseconds));
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

    for (auto &philosopher : philosophers) {
        threads.emplace_back(std::thread([&philosopher]() {
            philosopher.dine();
        }));
    }
    dinnerIsRunning->store(true);
    startTime = std::chrono::high_resolution_clock::now();
}

void DiningTable::endDinner() {
    dinnerIsRunning->store(false);
    for(auto &fork : forks) {
        fork->clearFromTable();
    }
    for (auto &thread : threads) {
        thread.join();
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    logger->info("Dinner ran for {}ms", totalTime);
    logger->info("Total fork wait time {}ms", forkWaitTimeMilliseconds->load());
}

