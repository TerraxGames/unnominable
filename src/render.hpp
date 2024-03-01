#ifndef UNNOMINABLE_RENDER_HPP_
#define UNNOMINABLE_RENDER_HPP_

#include "objects.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "world/camera.hpp"
#include <glad/gl.h>
#include <memory>

struct RenderVars {
    int  window_width  = 1280;
    int  window_height = 720;
    bool should_quit   = false;

    Shader shader;

    std::unique_ptr<world::Camera> camera;
    static constexpr float         camera_speed = 0.005f;

    std::unique_ptr<ImageTexture> texture0;
    std::unique_ptr<ImageTexture> texture1;

    GLint  success;
    GLchar info_log[512];

    std::unique_ptr<VertexArrayObject> VAO;
    std::unique_ptr<BufferObject>      VBO, EBO;
};

bool render_init(RenderVars *render_vars);

void render(RenderVars *render_vars, uint64_t delta_time);

void render_quit();

#endif // UNNOMINABLE_RENDER_HPP_
