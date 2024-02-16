#include "render.hpp"
#include "log.hpp"
#include "objects.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "util.hpp"
#include <glad/gl.h>
#include <utility>
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_log.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_timer.h>

const std::array<GLfloat, 8 * 4> vertices = {
    // position         // color          // tex-coords
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
    -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
};
const std::array<GLuint, 6> indices = {
    0, 1, 3, // first
    1, 2, 3, // second
};

bool render_init(RenderVars *render_vars) {
    int version =
        gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress));
    if (version == 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                        "Failed to initialize OpenGL");
        return false;
    }

#ifndef NDEBUG
    if (GLAD_GL_KHR_debug) {
        GLint flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

        if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT)) {
            SDL_LogDebug(UN_LOG_CATEGORY_OPENGL,
                         "Failed to enter a debug context! Consider using "
                         "glGetError().");
        }

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(UN_glDebugMessage, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                              nullptr, GL_TRUE);
    } else {
        SDL_LogDebug(UN_LOG_CATEGORY_OPENGL,
                     "KHR_debug extension not found! Consider implementing "
                     "ARB_debug_output.");
    }
#endif

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "OpenGL version %d.%d",
                GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glViewport(0, 0, render_vars->window_width, render_vars->window_height);

    glClearColor(0.3f, 0.1f, 0.3f, 1.0f);

    render_vars->shader = Shader();
    render_vars->shader.add_shader_path(ShaderType::VERTEX, "vertex.glsl");
    render_vars->shader.add_shader_path(ShaderType::FRAGMENT, "fragment.glsl");
    if (!render_vars->shader.compile_and_link()) {
        return false; // todo: use exceptions
    }

    // generate arrays/buffers
    auto VAO = std::make_unique<VertexArrayObject>();
    auto VBO = std::make_unique<BufferObject>(BufferType::ARRAY);
    auto EBO = std::make_unique<BufferObject>(BufferType::ELEMENT_ARRAY);
    VAO->bind();

    VBO->bind();
    VBO->upload_data(vertices, BufferUsage::STATIC_DRAW);

    EBO->bind();
    EBO->upload_data(indices, BufferUsage::STATIC_DRAW);

    VAO->init_vbo(8, GLtype::FLOAT);
    VAO->attrib_pointer_f(3, false); // a_pos
    VAO->enable_attrib_array();
    VAO->attrib_pointer_f(3, false); // a_color
    VAO->enable_attrib_array();
    VAO->attrib_pointer_f(2, false); // a_texcoord
    VAO->enable_attrib_array();

    VBO->unbind();
    // so we don't modify this VAO by accident; for cleanness' sake
    VAO->unbind();

    render_vars->VAO = std::move(VAO);
    render_vars->VBO = std::move(VBO);
    render_vars->EBO = std::move(EBO);

    // generate arrays/buffers
    // TODO: make abstractions for VAOs, VBOs, and EBOs
    // glGenVertexArrays(1, &render_vars->VAO);
    // glGenBuffers(1, &render_vars->VBO);
    // glGenBuffers(1, &render_vars->EBO);

    // // bind VAO
    // glBindVertexArray(render_vars->VAO);

    // // bind VBO
    // glBindBuffer(GL_ARRAY_BUFFER, render_vars->VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
    // GL_STATIC_DRAW);

    // // bind EBO
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_vars->EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
    //              GL_STATIC_DRAW);

    // // set vertex attribute pointers
    // std::size_t stride = 8 * sizeof(float);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0); //
    // a_pos glEnableVertexAttribArray(0); glVertexAttribPointer(
    //     1, 3, GL_FLOAT, GL_FALSE, stride,
    //     reinterpret_cast<void *>(3 * sizeof(float))); // a_color
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(
    //     2, 2, GL_FLOAT, GL_FALSE, stride,
    //     reinterpret_cast<void *>(6 * sizeof(float))); // a_texcoord
    // glEnableVertexAttribArray(2);

    // // unbind everything
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(
    //     0); // so we don't modify this VAO by accident; for cleanness' sake

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

void render(RenderVars *render_vars) {
    glClear(GL_COLOR_BUFFER_BIT);

    render_vars->shader.use();
    render_vars->shader.set_uniform_int("texture0", 0);
    render_vars->shader.set_uniform_int("texture1", 1);

    render_vars->texture0->bind_active(TextureUnit::U0);
    render_vars->texture1->bind_active(TextureUnit::U1);

    render_vars->VAO->bind();
    gl::draw_elements(gl::DrawMode::TRIANGLES, 6, GLtype::UNSIGNED_INT, 0);
}

void render_quit() {}
