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

const std::array<GLfloat, 36 * 8> vertices = {
    // positions         // normals           // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, //
    0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f, //
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, //
    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, //
    -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, //

    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //
    0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //
    -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //

    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, //
    -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, //
    -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, //
    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, //

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, //

    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 1.0f, //
    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, //
    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 0.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, //

    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, //
    0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f, //
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, //
    -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, //
    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, //
};

std::array<glm::vec3, 10> cube_positions = {
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

    gl::clear_color(0.1f, 0.1f, 0.1f, 1.0f);

    render_vars->object_shader = Shader();
    render_vars->object_shader.add_shader_path(ShaderType::VERTEX,
                                               "object.vert");
    render_vars->object_shader.add_shader_path(ShaderType::FRAGMENT,
                                               "object.frag");
    render_vars->object_shader.compile_and_link();

    render_vars->light_shader = Shader();
    render_vars->light_shader.add_shader_path(ShaderType::VERTEX,
                                              "generic.vert");
    render_vars->light_shader.add_shader_path(ShaderType::FRAGMENT,
                                              "light.frag");
    render_vars->light_shader.compile_and_link();

    // set up camera
    render_vars->camera =
        std::make_unique<world::Camera>(world::RenderPos(0.0f, 0.0f, 3.0f));

    // generate arrays/buffers
    auto VAO = std::make_unique<VertexArrayObject>();
    auto VBO = std::make_unique<BufferObject>(BufferType::ARRAY);
    VAO->bind();

    VBO->bind();
    VBO->upload_data(vertices, BufferUsage::STATIC_DRAW);

    VAO->init_vbo(8, GLtype::FLOAT);
    VAO->attrib_pointer_f(3, false); // a_pos
    VAO->enable_attrib_array();
    VAO->attrib_pointer_f(3, false); // a_normal
    VAO->enable_attrib_array();
    VAO->attrib_pointer_f(2, false); // a_texcoord
    VAO->enable_attrib_array();

    VBO->unbind();
    // so we don't modify this VAO by accident; for cleanness' sake
    VAO->unbind();

    render_vars->VAO = std::move(VAO);
    render_vars->VBO = std::move(VBO);

    auto container_tex =
        std::make_unique<ImageTexture>("textures/container2.png");
    container_tex->bind_generate();
    container_tex->default_parameters();
    container_tex->upload();
    container_tex->generate_mipmap();
    container_tex->free_surface();
    render_vars->container_tex = std::move(container_tex);

    auto container_specular_tex =
        std::make_unique<ImageTexture>("textures/container2_specular.png");
    container_specular_tex->bind_generate();
    container_specular_tex->default_parameters();
    container_specular_tex->upload();
    container_specular_tex->generate_mipmap();
    container_specular_tex->free_surface();
    render_vars->container_specular_tex = std::move(container_specular_tex);

    auto emissive_tex = std::make_unique<ImageTexture>("textures/matrix.jpg");
    emissive_tex->bind_generate();
    emissive_tex->default_parameters();
    emissive_tex->upload();
    emissive_tex->generate_mipmap();
    emissive_tex->free_surface();
    render_vars->emissive_tex = std::move(emissive_tex);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return true;
}

void render(RenderVars *render_vars, uint64_t delta_time) {
    gl::clear(gl::BufferBit::COLOR | gl::BufferBit::DEPTH);

    const auto  light_dir   = glm::vec3(-0.2f, -1.0f, -0.3f);
    const auto  light_color = glm::vec3(1.0f, 1.0f, 1.0f);
    const float luster      = 32.0f;

    render_vars->camera->apply_transformation();

    render_vars->object_shader.use();

    render_vars->VAO->bind();

    render_vars->object_shader.set_uniform_vec3f("u_light.direction",
                                                 light_dir);
    render_vars->object_shader.set_uniform_vec3f("u_light.ambient",
                                                 light_color / 5.0f);
    render_vars->object_shader.set_uniform_vec3f("u_light.diffuse",
                                                 light_color / 2.0f);
    render_vars->object_shader.set_uniform_vec3f("u_light.specular",
                                                 glm::vec3(1.0f));

    render_vars->container_tex->bind_active(TextureUnit::U0);
    render_vars->container_specular_tex->bind_active(TextureUnit::U1);
    render_vars->emissive_tex->bind_active(TextureUnit::U2);

    render_vars->object_shader.set_uniform_int("u_material.diffuse", 0);
    render_vars->object_shader.set_uniform_int("u_material.specular", 1);
    render_vars->object_shader.set_uniform_int("u_material.emissive", 2);
    render_vars->object_shader.set_uniform_float("u_material.luster", luster);

    render_vars->object_shader.set_uniform_mat4f("u_view",
                                                 render_vars->camera->view());

    float aspect_ratio = static_cast<float>(render_vars->window_width) /
                         render_vars->window_height;

    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);
    render_vars->object_shader.set_uniform_mat4f("u_projection", projection);

    auto model = glm::mat4(1.0f);
    render_vars->object_shader.set_uniform_mat4f("u_model", model);

    for (int i = 0; i < cube_positions.size(); i++) {
        auto pos = cube_positions.at(i);

        glm::mat4 object_model = glm::mat4(1.0f);
        object_model           = glm::translate(object_model, pos);
        float angle            = 20.0f * i;
        object_model           = glm::rotate(object_model, glm::radians(angle),
                                             glm::vec3(1.0f, 0.3f, 0.5f));
        render_vars->object_shader.set_uniform_mat4f("u_model", object_model);
        gl::draw_arrays(gl::DrawMode::TRIANGLES, 0, 36);
    }
}

void render_quit() {}
