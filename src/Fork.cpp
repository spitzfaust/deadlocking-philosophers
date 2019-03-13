#include <utility>

//
// Created by tobias on 3/9/19.
//

#include "Fork.h"

Fork::Fork(const unsigned long id, std::shared_ptr<std::atomic_ullong> waitTimeMilliseconds) :
        id(id),
        waitTimeMilliseconds(std::move(waitTimeMilliseconds)),
        mutex(std::mutex()),
        isInUse(false),
        conditionVariable(std::condition_variable()) {}


void Fork::use(const std::shared_ptr<std::atomic_bool> &continueTrying) {
    auto start = std::chrono::high_resolution_clock::now();
    std::unique_lock<std::mutex> lock(mutex);
    conditionVariable.wait(lock, [this, &continueTrying]() { return !isInUse && continueTrying->load(); });
    auto end = std::chrono::high_resolution_clock::now();
    waitTimeMilliseconds->fetch_add(
            static_cast<unsigned long long int>(std::chrono::duration_cast<std::chrono::milliseconds>(
                    end - start).count()),
            std::memory_order_relaxed);
}

void Fork::putBack() {
    mutex.unlock();
    conditionVariable.notify_all();
}

unsigned long Fork::getId() const {
    return id;
}

void Fork::clearFromTable() {
    conditionVariable.notify_all();
}
