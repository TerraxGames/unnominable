#include <glad/gl.h>
#include <SDL.h>
#include "render.hpp"

bool Init() {
    int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "OpenGL version %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);

    return true;
}

void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Quit() {}
