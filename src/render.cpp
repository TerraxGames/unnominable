#include <SDL_timer.h>
#include <glad/gl.h>
#include <SDL.h>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <stdint.h>
#include "render.hpp"
#include "shader.hpp"

const float vertices[] = {
     0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f,  1.0f,  0.0f, // bottom left
     0.0f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f, // top right
};

bool render_init(RenderVars *render_vars) {
    int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    if (version == 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize OpenGL\n");
        return false;
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "OpenGL version %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glViewport(0, 0, render_vars->window_width, render_vars->window_height);

    glClearColor(0.3f, 0.1f, 0.3f, 1.0f);

    render_vars->shader = Shader();
    render_vars->shader.add_shader_path(ShaderType::VERTEX, "vertex.glsl");
    render_vars->shader.add_shader_path(ShaderType::FRAGMENT, "fragment.glsl");
    if (!render_vars->shader.compile_and_link()) {
        return false; // todo: use exceptions
    }

    // generate arrays/buffers
    glGenVertexArrays(1, &render_vars->VAO);
    glGenBuffers(1, &render_vars->VBO);

    // bind VAO
    glBindVertexArray(render_vars->VAO);

    // bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, render_vars->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0); // aPos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float))); // aColor
    glEnableVertexAttribArray(1);

    // unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // so we don't modify this VAO by accident; for cleanness' sake

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return true;
}

void render(RenderVars *render_vars) {
    glClear(GL_COLOR_BUFFER_BIT);

    render_vars->shader.use();
    render_vars->shader.set_uniform_float("time", static_cast<float>(SDL_GetTicks()));

    glBindVertexArray(render_vars->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void render_quit() {}
