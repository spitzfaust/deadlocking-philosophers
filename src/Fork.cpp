//
// Created by tobias on 3/9/19.
//

#include "Fork.h"

Fork::Fork(const unsigned long id) : id(id), mutex(std::mutex()) {}


void Fork::use(const std::shared_ptr<std::atomic_bool> &continueTrying) {
    while (continueTrying->load() && !mutex.try_lock()) {}
}

void Fork::putBack() {
    mutex.unlock();
}

unsigned long Fork::getId() const {
    return id;
}
