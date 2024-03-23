#ifndef UNNOMINABLE_MAIN_HPP_
#define UNNOMINABLE_MAIN_HPP_
#include "render.hpp"
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_video.h>

void exit();

/// Miscellaneous cleanup code called pre-exit.
void pre_exit(SDL_GLContext &gl_context, SDL_Window *&window);

void handle_SDL_event(SDL_Event &event, render::RenderVars &render_vars);

void handle_keypress(render::RenderVars &render_vars, uint64_t delta_time);

void handle_mouse_motion(SDL_MouseMotionEvent &event,
                         render::RenderVars   &render_vars);

#endif // UNNOMINABLE_MAIN_HPP_
