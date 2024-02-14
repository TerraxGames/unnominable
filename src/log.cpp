#include "log.hpp"
#include <array>
#include <iostream>
#include <string>
#include <termstylist.h>
#include <SDL_log.h>

const std::array<std::string, SDL_LogPriority::SDL_NUM_LOG_PRIORITIES>
    PRIORITY_PREFIXES = {
        "UNKNOWN",
        termstylist::EO_FG816.FG_DarkGrey + "VERBOSE",
        termstylist::EO_FG816.FG_Blue + "DEBUG",
        termstylist::EO_FG816.FG_Green + "INFO",
        termstylist::EO_FG816.FG_Yellow + "WARN",
        termstylist::EO_FG816.FG_Red + "ERROR",
        termstylist::EO_FG256.FG256_160 + "CRITICAL",
};

const std::array<std::string, SDL_LogCategory::SDL_LOG_CATEGORY_CUSTOM>
    CATEGORY_PREFIXES = {
        "App",      "Error",    "Assert",   "System",   "Audio",
        "Video",    "Render",   "Input",    "Test",     "Reserved",
        "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
        "Reserved", "Reserved", "Reserved", "Reserved",
};

void UN_LogOutputFunction(void *userdata, int category,
                          SDL_LogPriority priority, const char *message) {
    LogOptions *options = reinterpret_cast<LogOptions *>(userdata);
    if (options == nullptr) {
        std::cout << "(Logger) "
                  << UN_LogGetPriorityPrefix(SDL_LOG_PRIORITY_CRITICAL)
                  << "  Invalid LogOptions!";
    }
    if (options->print_category) {
        std::cout << "(" << UN_LogGetCategoryPrefix(category) << ") ";
    }

    std::cout << UN_LogGetPriorityPrefix(priority) << "  " << message
              << termstylist::RESET_Default << "\n";
}

const std::string &UN_LogGetPriorityPrefix(SDL_LogPriority priority) {
    return PRIORITY_PREFIXES[priority];
}

const std::string &UN_LogGetCategoryPrefix(int category) {
    return CATEGORY_PREFIXES[category];
}

void UN_LogSetOptions(LogOptions &options) {
    SDL_LogSetOutputFunction(UN_LogOutputFunction, &options);
}
