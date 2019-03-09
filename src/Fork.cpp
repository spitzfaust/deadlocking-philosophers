//
// Created by tobias on 3/9/19.
//

#include "Fork.h"

Fork::Fork(const unsigned long id) : id(id), mutex(std::mutex()) {}


void Fork::use() {
    mutex.lock();
}

void Fork::putBack() {
    mutex.unlock();
}

unsigned long Fork::getId() const {
    return id;
}
