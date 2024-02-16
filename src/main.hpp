#ifndef UNNOMINABLE_MAIN_HPP_
#define UNNOMINABLE_MAIN_HPP_
#include "render.hpp"
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_video.h>

void exit();

/// Miscellaneous cleanup code called pre-exit.
void pre_exit(SDL_GLContext &gl_context, SDL_Window *&window);

void handle_SDL_event(SDL_Event *event, RenderVars *render_vars);

#endif // UNNOMINABLE_MAIN_HPP_
