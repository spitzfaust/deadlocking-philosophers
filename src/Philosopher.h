//
// Created by tobias on 3/9/19.
//

#ifndef PHILOSOPHERS_PHILOSOPHER_H
#define PHILOSOPHERS_PHILOSOPHER_H

#include <memory>
#include "Fork.h"
#include "RandomIntGenerator.h"
#include "Logger.h"

class Philosopher {
public:
    Philosopher(unsigned long id, int maxThinkingTimeInMilliseconds,
                int maxEatingTimeInMilliseconds, const std::shared_ptr<Fork> &rightFork,
                const std::shared_ptr<Fork> &leftFork,
                std::shared_ptr<std::atomic_bool> dinnerIsRunning,
                std::shared_ptr<RandomIntGenerator> randomIntGenerator,
                std::shared_ptr<Logger> logger);

    void dine();

private:
    void think() const;

    void takeFork(std::shared_ptr<Fork> fork);

    void eat() const;

    void putBackForks();

    int getRandomIntBetweenZeroAnd(int high) const;

    const std::shared_ptr<Logger> logger;
    const std::shared_ptr<RandomIntGenerator> randomIntGenerator;
    const std::shared_ptr<Fork> rightFork;
    const std::shared_ptr<Fork> leftFork;
    const std::shared_ptr<std::atomic_bool> dinnerInProgress;
    const unsigned long id;
    const int maxThinkingTimeInMilliseconds;
    const int maxEatingTimeInMilliseconds;
};


#endif //PHILOSOPHERS_PHILOSOPHER_H
