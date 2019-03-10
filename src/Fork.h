//
// Created by tobias on 3/9/19.
//

#ifndef PHILOSOPHERS_FORK_H
#define PHILOSOPHERS_FORK_H


#include <mutex>
#include <atomic>
#include <memory>

class Fork {

public:
    Fork(unsigned long id);

    void use(const std::shared_ptr<std::atomic_bool> &continueTrying);

    void putBack();

    unsigned long getId() const;

private:
    std::mutex mutex;
    const unsigned long id;
};


#endif //PHILOSOPHERS_FORK_H
