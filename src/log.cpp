#include "log.hpp"
#include <array>
#include <glad/gl.h>
#include <iostream>
#include <string>
#include <termstylist.h>
#include <SDL_log.h>

const std::array<std::string, SDL_NUM_LOG_PRIORITIES> PRIORITY_PREFIXES = {
    "",
    termstylist::EO_FG816.FG_DarkGrey + "VERBOSE",
    termstylist::EO_FG816.FG_Blue + "DEBUG",
    termstylist::EO_FG816.FG_Green + "INFO",
    termstylist::EO_FG816.FG_Yellow + "WARN",
    termstylist::EO_FG816.FG_Red + "ERROR",
    termstylist::EO_FG256.FG256_160 + "CRITICAL",
};

const std::array<std::string, UN_NUM_LOG_CATEGORIES> CATEGORY_PREFIXES = {
    "App",       "Error",     "Assert",    "System",     "Audio",
    "Video",     "Render",    "Input",     "Test",       "Reserved1",
    "Reserved2", "Reserved3", "Reserved4", "Reserved5",  "Reserved6",
    "Reserved7", "Reserved8", "Reserved9", "Reserved10", "Custom",
    "OpenGL",    "Assimp",
};

const std::array<std::string, 4> GL_DEBUG_SEVERITY_PREFIXES = {
    termstylist::EO_FG816.FG_Red + "HIGH",
    termstylist::EO_FG816.FG_Yellow + "MEDIUM",
    termstylist::EO_FG816.FG_Green + "LOW",
    termstylist::EO_FG816.FG_Blue + "NOTIFICATION",
};

void UN_LogOutputFunction(void *userdata, int category,
                          SDL_LogPriority priority, const char *message) {
    if (userdata == nullptr) {
        std::cout << "(Logger) "
                  << UN_LogGetPriorityPrefix(SDL_LOG_PRIORITY_ERROR)
                  << "  LogOptions is nullptr! Try setting the userdata "
                     "argument to an instance of LogOptions."
                  << termstylist::RESET_Default << "\n";
        return;
    }

    LogOptions *options =
        /* spooky! */ reinterpret_cast<LogOptions *>(userdata);
    if (options->print_category) {
        std::cout << "(" << UN_LogGetCategoryPrefix(category) << ") ";
    }

    if (priority > 0) {
        std::cout << UN_LogGetPriorityPrefix(priority) << "  ";
    }

    std::cout << message << termstylist::RESET_Default << "\n";
}

const std::string &UN_LogGetPriorityPrefix(SDL_LogPriority priority) {
    return PRIORITY_PREFIXES.at(priority);
}

const std::string &UN_LogGetCategoryPrefix(int category) {
    return CATEGORY_PREFIXES.at(category);
}

const char *UN_glGetDebugSeverityPrefix(GLenum severity) {
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        return GL_DEBUG_SEVERITY_PREFIXES[0].c_str();
    case GL_DEBUG_SEVERITY_MEDIUM:
        return GL_DEBUG_SEVERITY_PREFIXES[1].c_str();
    case GL_DEBUG_SEVERITY_LOW:
        return GL_DEBUG_SEVERITY_PREFIXES[2].c_str();
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        return GL_DEBUG_SEVERITY_PREFIXES[3].c_str();
    }
    return "UNKNOWN_SEVERITY";
}

const char *UN_glGetDebugTypePrefix(GLenum type) {
    switch (type) {
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return "DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return "UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_ERROR:
        return "ERROR";
    case GL_DEBUG_TYPE_MARKER:
        return "MARKER";
    case GL_DEBUG_TYPE_OTHER:
        return "OTHER";
    case GL_DEBUG_TYPE_PERFORMANCE:
        return "PERFORMANCE";
    case GL_DEBUG_TYPE_POP_GROUP:
        return "POP_GROUP";
    case GL_DEBUG_TYPE_PUSH_GROUP:
        return "PUSH_GROUP";
    case GL_DEBUG_TYPE_PORTABILITY:
        return "PORTABILITY";
    }
    return "UNKNOWN_TYPE";
}

const char *UN_glGetDebugSourcePrefix(GLenum source) {
    switch (source) {
    case GL_DEBUG_SOURCE_API:
        return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return "Window System";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        return "Shader Compiler";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return "Third-Party";
    case GL_DEBUG_SOURCE_APPLICATION:
        return "Application";
    case GL_DEBUG_SOURCE_OTHER:
        return "Other";
    }
    return "Unknown Source";
}

void UN_LogSetOptions(LogOptions &options) {
    SDL_LogSetOutputFunction(UN_LogOutputFunction, &options);
}

void GLAD_API_PTR UN_glDebugMessage(GLenum source, GLenum type, GLuint id,
                                    GLenum severity, GLsizei length,
                                    const GLchar *message,
                                    const void   *user_param) {
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;
    SDL_LogMessage(UN_LOG_CATEGORY_OPENGL, static_cast<SDL_LogPriority>(0),
                   "{%s/%s} %s  %s", UN_glGetDebugSourcePrefix(source),
                   UN_glGetDebugTypePrefix(type),
                   UN_glGetDebugSeverityPrefix(severity), message);
}
