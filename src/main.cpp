#include <iostream>
#include "cxxopts/cxxopts.hpp"
#include "DiningTable.h"
#include "spdlog/spdlog.h"

int main(int argc, char *argv[]) {
    int numberOfPhilosophers = 0;
    int maxThinkingTimeInMilliseconds = 0;
    int maxEatingTimeInMilliseconds = 0;
    try {
        // Initialize program options and parse them
        cxxopts::Options options(argv[0], "Concurrency - Dining Philosophers");
        options.positional_help("[optional args]")
                .show_positional_help();
        options.add_options()
                ("n,philosophers", "number of philosophers", cxxopts::value<int>(numberOfPhilosophers))
                ("t,thinking", "maximal thinking time of philosophers in milliseconds",
                 cxxopts::value<int>(maxThinkingTimeInMilliseconds))
                ("e,eating", "maximal eating time of philosophers in milliseconds",
                 cxxopts::value<int>(maxEatingTimeInMilliseconds))
                ("h,help", "print help");
        auto parsedOptions = options.parse(argc, argv);
        if (parsedOptions.count("help")) {
            std::cout << options.help({"", "Group"}) << std::endl;
            return EXIT_SUCCESS;
        }

        if (numberOfPhilosophers <= 0 || maxThinkingTimeInMilliseconds <= 0 || maxEatingTimeInMilliseconds <= 0) {
            std::cerr << "All options have to be > 0" << std::endl;
            return EXIT_FAILURE;
        }

    } catch (const cxxopts::OptionException &e) {
        std::cerr << "error parsing options: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Number of philosophers: " << numberOfPhilosophers << std::endl
              << "Max thinking time: " << maxThinkingTimeInMilliseconds << std::endl
              << "Max eating time: " << maxEatingTimeInMilliseconds << std::endl;

    auto logger = std::make_shared<Logger>(spdlog::default_logger());
    auto diningTable = DiningTable(static_cast<unsigned long>(numberOfPhilosophers), maxThinkingTimeInMilliseconds,
                                   maxEatingTimeInMilliseconds,
                                   logger);

    diningTable.startDinner();

    std::cin.get();

    diningTable.endDinner();

    return EXIT_SUCCESS;
}