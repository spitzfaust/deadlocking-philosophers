#include <utility>

//
// Created by tobias on 3/9/19.
//

#ifndef PHILOSOPHERS_LOGGER_H
#define PHILOSOPHERS_LOGGER_H

#include "spdlog/logger.h"

class Logger {
public:

private:
public:
    Logger(std::shared_ptr<spdlog::logger> logger) : logger(std::move(logger)) {}


    template<typename... Args>
    void info(const char *fmt, const Args... args) const {
        logger->info(fmt, std::forward<const Args>(args)...);
    }

private:
    const std::shared_ptr<spdlog::logger> logger;
};

#endif //PHILOSOPHERS_LOGGER_H
