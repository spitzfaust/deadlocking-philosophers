#include <utility>

//
// Created by tobias on 3/9/19.
//

#include "Fork.h"

Fork::Fork(const unsigned long id, std::shared_ptr<std::atomic_ullong> waitTimeMilliseconds) :
        id(id),
        waitTimeMilliseconds(std::move(waitTimeMilliseconds)),
        mutex(std::mutex()) {}


void Fork::use(const std::shared_ptr<std::atomic_bool> &continueTrying) {
    auto start = std::chrono::high_resolution_clock::now();
    while (continueTrying->load() && !mutex.try_lock()) {}
    auto end = std::chrono::high_resolution_clock::now();
    waitTimeMilliseconds->fetch_add(
            static_cast<unsigned long long int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()),
            std::memory_order_relaxed);
}

void Fork::putBack() {
    mutex.unlock();
}

unsigned long Fork::getId() const {
    return id;
}
