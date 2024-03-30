#ifndef UNNOMINABLE_LOG_HPP_
#define UNNOMINABLE_LOG_HPP_
#include <glad/gl.h>
#include <string>
#include <SDL.h>
#include <SDL_log.h>

#ifdef NDEBUG
#define UN_LOG_PRIORITY SDL_LOG_PRIORITY_INFO
#else
#define UN_LOG_PRIORITY SDL_LOG_PRIORITY_DEBUG
#endif

enum UN_LogCategory {
    UN_LOG_CATEGORY_CUSTOM = SDL_LOG_CATEGORY_CUSTOM,
    UN_LOG_CATEGORY_OPENGL,
    UN_LOG_CATEGORY_ASSIMP,

    UN_NUM_LOG_CATEGORIES,
};

struct LogOptions {
    bool print_category = true;
};

void UN_LogOutputFunction(void *userdata, int category,
                          SDL_LogPriority priority, const char *message);

const std::string &UN_LogGetPriorityPrefix(SDL_LogPriority priority);
const std::string &UN_LogGetCategoryPrefix(int category);

void UN_LogSetOptions(LogOptions &options);

void GLAD_API_PTR UN_glDebugMessage(GLenum source, GLenum type, GLuint id,
                                    GLenum severity, GLsizei length,
                                    const GLchar *message,
                                    const void   *user_param);

#endif // UNNOMINABLE_LOG_HPP_
