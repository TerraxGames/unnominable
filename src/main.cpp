#include "main.hpp"
#include "log.hpp"
#include <iostream>
#include <SDL_image.h>
#include <SDL_log.h>

#ifdef NDEBUG
#define UN_LOG_PRIORITY SDL_LOG_PRIORITY_INFO
#else
#define UN_LOG_PRIORITY SDL_LOG_PRIORITY_DEBUG
#endif

int main() {
    // set up logging
    LogOptions log_options = {};
    UN_LogSetOptions(log_options);
    SDL_LogSetAllPriority(UN_LOG_PRIORITY);
    SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_INFO);

    auto render_vars = RenderVars{};

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Initialize SDL_image
    int sdl_image_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_Init(sdl_image_flags) != sdl_image_flags) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to initialize SDL_image: %s", SDL_GetError());
        return 1;
    }

    // we don't care about MacOS support, so go ham
    // we'll use Vulkan when implementing raytracing
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    // don't disable compositing
    // todo: add option in settings to disable the compositor
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

    int window_flags =
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    SDL_Window *window = SDL_CreateWindow(
        "Unnominable", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        render_vars.window_width, render_vars.window_height, window_flags);
    if (!window) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to create OpenGL context: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Enable VSync
    SDL_GL_SetSwapInterval(-1);

    // Initialize OpenGL
    if (render_init(&render_vars)) {
        SDL_Event event;

        while (!render_vars.should_quit) {
            while (SDL_PollEvent(&event)) {
                handle_SDL_event(&event, &render_vars);
            }

            render(&render_vars);

            // Swap framebuffer
            SDL_GL_SwapWindow(window);
        }

        render_quit();
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

void handle_SDL_event(SDL_Event *event, RenderVars *render_vars) {
    if (event->type == SDL_QUIT) {
        render_vars->should_quit = true;
    } else if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_ESCAPE:
            render_vars->should_quit = true;
            break;
        }
    }

    if (event->type == SDL_WINDOWEVENT) {
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            int window_width  = event->window.data1;
            int window_height = event->window.data2;
            glViewport(0, 0, window_width, window_height);

            render_vars->window_width  = window_width;
            render_vars->window_height = window_height;
            break;
        }
    }
}
