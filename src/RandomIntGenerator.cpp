//
// Created by tobias on 3/9/19.
//

#include "RandomIntGenerator.h"

int RandomIntGenerator::generateRandomIntBetween(const int low, const int high) {
    auto randomDevice = std::random_device();
    auto generator = std::mt19937(randomDevice());
    static thread_local std::uniform_int_distribution<int> distribution(low, high);
    return distribution(generator);
}
