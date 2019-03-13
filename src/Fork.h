//
// Created by tobias on 3/9/19.
//

#ifndef PHILOSOPHERS_FORK_H
#define PHILOSOPHERS_FORK_H


#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>

class Fork {

public:
    Fork(unsigned long id, std::shared_ptr<std::atomic_ullong> waitTimeMilliseconds);

    void use(const std::shared_ptr<std::atomic_bool> &continueTrying);

    void putBack();

    void clearFromTable();

    unsigned long getId() const;

private:
    std::shared_ptr<std::atomic_ullong> waitTimeMilliseconds;
    std::mutex mutex;
    std::condition_variable conditionVariable;
    const unsigned long id;
    bool isInUse;
};


#endif //PHILOSOPHERS_FORK_H
