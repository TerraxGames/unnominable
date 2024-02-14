#ifndef UNNOMINABLE_LOG_HPP_
#define UNNOMINABLE_LOG_HPP_
#include <string>
#include <SDL.h>
#include <SDL_log.h>

struct LogOptions {
    bool print_category = true;
};

void UN_LogOutputFunction(void *userdata, int category,
                          SDL_LogPriority priority, const char *message);

const std::string &UN_LogGetPriorityPrefix(SDL_LogPriority priority);
const std::string &UN_LogGetCategoryPrefix(int category);

void UN_LogSetOptions(LogOptions &options);

#endif // UNNOMINABLE_LOG_HPP_
