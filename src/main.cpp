#include "main.hpp"
#include "log.hpp"
#include "math.hpp"
#include "termstylist.h"
#include "util.hpp"
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_log.h>
#include <SDL_mouse.h>
#include <SDL_scancode.h>
#include <SDL_stdinc.h>
#include <SDL_video.h>

int main() {
    // set up logging
    LogOptions log_options{};
    UN_LogSetOptions(log_options);
    SDL_LogSetAllPriority(UN_LOG_PRIORITY);
    SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_INFO);
    SDL_LogSetPriority(UN_LOG_CATEGORY_OPENGL, static_cast<SDL_LogPriority>(0));

#ifndef NDEBUG
    // clear the console for convenience
    std::cout << termstylist::ATTRS_Clear;
#endif

    auto render_vars = render::RenderVars{};

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Initialize SDL_image
    int sdl_image_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_Init(sdl_image_flags) != sdl_image_flags) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to initialize SDL_image: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // we don't care about MacOS support, so go ham
    // we'll use Vulkan when implementing raytracing
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
#ifndef NDEBUG
    // enable debugging if we're in debug
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

    // don't disable compositing
    // todo: add option in settings to disable the compositor
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

    // set exit function
    const int exit_registration_result = std::atexit(exit);
    if (exit_registration_result) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "atexit registration failed!");
        return EXIT_FAILURE;
    }

    int window_flags =
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    SDL_Window *window = SDL_CreateWindow(
        "Unnominable", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        render_vars.window_width, render_vars.window_height, window_flags);
    if (window == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to create window: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    render_vars.window_id = SDL_GetWindowID(window);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (gl_context == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to create OpenGL context: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return EXIT_FAILURE;
    }

    // Enable VSync
    SDL_GL_SetSwapInterval(-1);

    // Enable Window Grab
    int supported = SDL_SetRelativeMouseMode(SDL_TRUE);
    if (!supported) {
        supported = SDL_CaptureMouse(SDL_TRUE);
    }
    if (!supported) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "No mouse capture method supported!");
        return EXIT_FAILURE;
    }

    uint64_t last_frame = util::get_ms<uint64_t>();

    try {
        // Initialize OpenGL
        if (render::init(&render_vars)) {
            SDL_Event event;

            while (!render_vars.should_quit) {
                uint64_t current_frame = util::get_ms<uint64_t>();
                uint64_t delta_time    = current_frame - last_frame;

                while (SDL_PollEvent(&event)) {
                    handle_SDL_event(event, render_vars);
                }
                handle_keypress(render_vars, delta_time);

                render::render(&render_vars, delta_time);

                last_frame = current_frame;

                // Swap framebuffer
                SDL_GL_SwapWindow(window);
            }

            render::quit();
        }
    } catch (std::exception &e) {
        if (strlen(e.what()) > 0) {
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", e.what());
        }
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                        "Unhandled exception! Quitting now.");
        pre_exit(gl_context, window);
        return EXIT_FAILURE;
    }

    pre_exit(gl_context, window);

    return EXIT_SUCCESS;
}

void exit() {
    IMG_Quit();
    SDL_Quit();
}

/// Miscellaneous cleanup code called pre-exit.
void pre_exit(SDL_GLContext &gl_context, SDL_Window *&window) {
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
}

void handle_SDL_event(SDL_Event &event, render::RenderVars &render_vars) {
    if (event.type == SDL_QUIT) {
        render_vars.should_quit = true;
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            render_vars.should_quit = true;
            break;
        }
    }

    if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            int window_width  = event.window.data1;
            int window_height = event.window.data2;
            gl::viewport(0, 0, window_width, window_height);

            render_vars.window_width  = window_width;
            render_vars.window_height = window_height;
            break;
        }
    }

    uint32_t flags =
        SDL_GetWindowFlags(SDL_GetWindowFromID(event.window.windowID));
    bool is_minimized = flags & SDL_WINDOW_MINIMIZED;
    bool is_focused =
        (flags & SDL_WINDOW_INPUT_FOCUS) && (flags & SDL_WINDOW_MOUSE_FOCUS);
    if (event.type == SDL_MOUSEMOTION && !is_minimized && is_focused) {
        handle_mouse_motion(event.motion, render_vars);
    }
}

void handle_keypress(render::RenderVars &render_vars, uint64_t delta_time) {
    const uint8_t *state        = SDL_GetKeyboardState(nullptr);
    float          camera_speed = render_vars.camera_speed * delta_time;

    if (state[SDL_SCANCODE_W]) {
        render_vars.camera->position +=
            camera_speed * render_vars.camera->forward();
    }
    if (state[SDL_SCANCODE_A]) {
        render_vars.camera->position -=
            camera_speed * render_vars.camera->right();
    }
    if (state[SDL_SCANCODE_S]) {
        render_vars.camera->position -=
            camera_speed * render_vars.camera->forward();
    }
    if (state[SDL_SCANCODE_D]) {
        render_vars.camera->position +=
            camera_speed * render_vars.camera->right();
    }
    if (state[SDL_SCANCODE_SPACE]) {
        render_vars.camera->position += camera_speed * math::Direction::UP;
    }
    if (state[SDL_SCANCODE_LSHIFT]) {
        render_vars.camera->position -= camera_speed * math::Direction::UP;
    }
}

void handle_mouse_motion(SDL_MouseMotionEvent &event,
                         render::RenderVars   &render_vars) {
    // https://gamedev.stackexchange.com/a/30654/178226
    // special thanks to ltjax on Gamedev Stack Exchange for solving this
    // problem!
    float      x_movement = event.xrel * render_vars.camera->sensitivity;
    float      y_movement = event.yrel * render_vars.camera->sensitivity;
    glm::quat &rotation   = render_vars.camera->rotation;
    float     &pitch      = render_vars.camera->pitch;
    float     &yaw        = render_vars.camera->yaw;
    // reset rotation
    rotation              = glm::quat_identity<float, glm::defaultp>();

    float pitch_result = pitch + y_movement;
    if (pitch_result > -90.0f && pitch_result < 90.0f) {
        pitch += y_movement;
    }
    yaw      += x_movement;
    rotation  = glm::angleAxis(glm::radians(pitch), math::Direction::EAST) *
               rotation *
               glm::angleAxis(glm::radians(yaw), math::Direction::UP);
}
