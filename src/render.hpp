#ifndef UNNOMINABLE_RENDER_HPP_
#define UNNOMINABLE_RENDER_HPP_

#include "shader.hpp"
#include "texture.hpp"
#include <concepts>
#include <glad/gl.h>

struct RenderVars {
    int                           window_width  = 1280;
    int                           window_height = 720;
    bool                          should_quit   = false;
    Shader                        shader;
    std::unique_ptr<ImageTexture> texture0;
    std::unique_ptr<ImageTexture> texture1;
    GLint                         success;
    GLchar                        info_log[512];
    GLuint                        VAO, VBO, EBO;
};

bool render_init(RenderVars *render_vars);

void render(RenderVars *render_vars);

void render_quit();

#endif // UNNOMINABLE_RENDER_HPP_
