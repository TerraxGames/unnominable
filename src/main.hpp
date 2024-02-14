#ifndef UNNOMINABLE_MAIN_HPP_
#define UNNOMINABLE_MAIN_HPP_
#include "render.hpp"
#include <glad/gl.h>
#include <SDL.h>

void exit();

void handle_SDL_event(SDL_Event *event, RenderVars *render_vars);

#endif // UNNOMINABLE_MAIN_HPP_
