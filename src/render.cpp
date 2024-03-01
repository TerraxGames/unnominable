#include "render.hpp"
#include "log.hpp"
#include "objects.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "util.hpp"
#include "world/camera.hpp"
#include "world/world.hpp"
#include <glad/gl.h>
#include <memory>
#include <utility>
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_log.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_timer.h>

const std::array<GLfloat, 36 * 5> vertices = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
    0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //

    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //
    -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, //
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
};

glm::vec3 cube_positions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),     //
    glm::vec3(2.0f, 5.0f, -15.0f),   //
    glm::vec3(-1.5f, -2.2f, -2.5f),  //
    glm::vec3(-3.8f, -2.0f, -12.3f), //
    glm::vec3(2.4f, -0.4f, -3.5f),   //
    glm::vec3(-1.7f, 3.0f, -7.5f),   //
    glm::vec3(1.3f, -2.0f, -2.5f),   //
    glm::vec3(1.5f, 2.0f, -2.5f),    //
    glm::vec3(1.5f, 0.2f, -1.5f),    //
    glm::vec3(-1.3f, 1.0f, -1.5f),   //
};

bool render_init(RenderVars *render_vars) {
    int version =
        gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress));
    if (version == 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to initialize OpenGL");
        return false;
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "OpenGL version %d.%d",
                GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

#ifndef NDEBUG
    if (GLAD_GL_KHR_debug) {
        GLint flags;
        gl::get_integerv(gl::Variable::CONTEXT_FLAGS, &flags);

        if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT)) {
            SDL_LogDebug(UN_LOG_CATEGORY_OPENGL,
                         "Failed to enter a debug context! Consider using "
                         "glGetError().");
        }

        gl::enable(gl::Capability::DEBUG_OUTPUT);
        gl::enable(gl::Capability::DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(UN_glDebugMessage, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                              nullptr, GL_TRUE);
    } else {
        SDL_LogDebug(UN_LOG_CATEGORY_OPENGL,
                     "KHR_debug extension not found! Consider implementing "
                     "ARB_debug_output.");
    }
#endif

    gl::enable(gl::Capability::DEPTH_TEST);

    gl::viewport(0, 0, render_vars->window_width, render_vars->window_height);

    gl::clear_color(0.3f, 0.1f, 0.3f, 1.0f);

    render_vars->shader = Shader();
    render_vars->shader.add_shader_path(ShaderType::VERTEX, "shader.vert");
    render_vars->shader.add_shader_path(ShaderType::FRAGMENT, "shader.frag");
    if (!render_vars->shader.compile_and_link()) {
        return false; // todo: use exceptions
    }

    // set up camera
    render_vars->camera =
        std::make_unique<world::Camera>(world::RenderPos(0.0f, 0.0f, 3.0f));

    // generate arrays/buffers
    auto VAO = std::make_unique<VertexArrayObject>();
    auto VBO = std::make_unique<BufferObject>(BufferType::ARRAY);
    VAO->bind();

    VBO->bind();
    VBO->upload_data(vertices, BufferUsage::STATIC_DRAW);

    VAO->init_vbo(5, GLtype::FLOAT);
    VAO->attrib_pointer_f(3, false); // a_pos
    VAO->enable_attrib_array();
    VAO->attrib_pointer_f(2, false); // a_texcoord
    VAO->enable_attrib_array();

    VBO->unbind();
    // so we don't modify this VAO by accident; for cleanness' sake
    VAO->unbind();

    render_vars->VAO = std::move(VAO);
    render_vars->VBO = std::move(VBO);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // load first texture
    auto texture0 = std::make_unique<ImageTexture>("textures/container.jpg");
    texture0->bind_generate();
    texture0->default_parameters();
    texture0->upload();
    texture0->generate_mipmap();
    texture0->free_surface();
    render_vars->texture0 = std::move(texture0);

    // load second texture
    auto texture1 = std::make_unique<ImageTexture>("textures/awesomeface.png");
    texture1->bind_generate();
    texture1->default_parameters();
    texture1->upload();
    texture1->generate_mipmap();
    texture1->free_surface();
    render_vars->texture1 = std::move(texture1);

    return true;
}

void render(RenderVars *render_vars, uint64_t delta_time) {
    gl::clear(gl::BufferBit::COLOR | gl::BufferBit::DEPTH);

    render_vars->shader.use();
    render_vars->shader.set_uniform_int("u_texture0", 0);
    render_vars->shader.set_uniform_int("u_texture1", 1);

    render_vars->texture0->bind_active(TextureUnit::U0);
    render_vars->texture1->bind_active(TextureUnit::U1);

    render_vars->VAO->bind();

    render_vars->camera->apply_transformation();
    render_vars->shader.set_uniform_mat4f("view", render_vars->camera->view());

    float aspect_ratio = static_cast<float>(render_vars->window_width) /
                         render_vars->window_height;

    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);
    render_vars->shader.set_uniform_mat4f("projection", projection);

    for (auto &cube_pos : cube_positions) {
        auto i = &cube_pos - &cube_positions[0];

        auto model = glm::mat4(1.0f);
        model = glm::translate(model, cube_pos + glm::vec3(0.0f, 0.0f, 0.0f));
        float angle = i * glm::radians(50.0f);
        model       = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));
        render_vars->shader.set_uniform_mat4f("model", model);

        gl::draw_arrays(gl::DrawMode::TRIANGLES, 0, 36);
    }
}

void render_quit() {}
