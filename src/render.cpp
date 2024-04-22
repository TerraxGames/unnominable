#include "render.hpp"
#include "log.hpp"
#include "math.hpp" // IWYU pragma: keep
#include "model.hpp"
#include "objects.hpp"
#include "shader.hpp"
#include "types.hpp"
#include "util.hpp"
#include "world/camera.hpp"
#include "world/planet.hpp"
#include "world/world.hpp"
#include <memory>
#include <ranges>
#include <utility>

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/vector2.h>
#include <assimp/vector3.h>
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_log.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_timer.h>

namespace render {

const std::array<GLfloat, 36 * 8> vertices = {
    // positions         // normals           // texture coords
    -1.0f, -1.0f, -1.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, //
    1.0f,  -1.0f, -1.0f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f, //
    1.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, //
    1.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, //
    -1.0f, 1.0f,  -1.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f, //
    -1.0f, -1.0f, -1.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, //

    -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //
    1.0f,  -1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, //
    1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //
    1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, //
    -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, //
    -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, //

    -1.0f, 1.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, //
    -1.0f, 1.0f,  -1.0f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, //
    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, //
    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, //
    -1.0f, -1.0f, 1.0f,  -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, //
    -1.0f, 1.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, //

    1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, //
    1.0f,  1.0f,  -1.0f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, //
    1.0f,  -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, //
    1.0f,  -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, //
    1.0f,  -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, //
    1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, //

    -1.0f, -1.0f, -1.0f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, //
    1.0f,  -1.0f, -1.0f, 0.0f,  -1.0f, 0.0f,  1.0f, 1.0f, //
    1.0f,  -1.0f, 1.0f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, //
    1.0f,  -1.0f, 1.0f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, //
    -1.0f, -1.0f, 1.0f,  0.0f,  -1.0f, 0.0f,  0.0f, 0.0f, //
    -1.0f, -1.0f, -1.0f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, //

    -1.0f, 1.0f,  -1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, //
    1.0f,  1.0f,  -1.0f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f, //
    1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, //
    1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, //
    -1.0f, 1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, //
    -1.0f, 1.0f,  -1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, //
};

std::vector<PointLight> point_lights = {
    // PointLight{
    //     .position  = glm::vec3(1.2f, 1.0f, 2.0f),
    //     .diffuse   = glm::vec3(0.5f),
    //     .specular  = glm::vec3(1.0f),
    //     .constant  = 1.0f,
    //     .linear    = 0.09f,
    //     .quadratic = 0.032f,
    // },
    // PointLight{
    //     .position  = glm::vec3(-2.5f, 2.0f, -1.5f),
    //     .diffuse   = glm::vec3(0.75f, 0.25f, 0.75f),
    //     .specular  = glm::vec3(1.0f, 0.5f, 1.0f),
    //     .constant  = 1.0f,
    //     .linear    = 0.045f,
    //     .quadratic = 0.0075f,
    // },
    // PointLight{
    //     .position  = glm::vec3(0.0f, 0.0f, -3.0f),
    //     .diffuse   = glm::vec3(0.75f, 0.0f, 0.0f),
    //     .specular  = glm::vec3(1.0f, 0.0f, 0.0f),
    //     .constant  = 1.0f,
    //     .linear    = 0.09f,
    //     .quadratic = 0.032f,
    // },
};

std::vector<Model> models{};

std::map<size_t, std::vector<glm::vec3>> model_positions = {
    // {
    //     0,
    //     {
    //         glm::vec3(0.0f, 0.0f, 0.0f),
    //         // glm::vec3(2.0f, 5.0f, -15.0f),
    //         // glm::vec3(-3.0f, -2.0f, -3.0f),
    //         // glm::vec3(-4.0f, -2.0f, -12.0f),
    //         // glm::vec3(2.4f, -0.4f, -3.5f),
    //         // glm::vec3(-1.7f, 3.0f, -7.5f),
    //         // glm::vec3(1.3f, -2.0f, -2.5f),
    //         // glm::vec3(1.5f, 2.0f, -2.5f),
    //         // glm::vec3(1.5f, 0.2f, -1.5f),
    //         // glm::vec3(-1.3f, 1.0f, -1.5f),
    //     },
    // },
};

bool init(RenderVars *render_vars) {
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
        gl::debug_message_callback(UN_glDebugMessage, nullptr);
        gl::debug_message_control(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                                  nullptr, GL_TRUE);
    } else {
        SDL_LogDebug(UN_LOG_CATEGORY_OPENGL,
                     "KHR_debug extension not found! Consider implementing "
                     "ARB_debug_output.");
    }
#endif

    gl::enable(gl::Capability::DEPTH_TEST);
    gl::enable(gl::Capability::CULL_FACE);
    glCullFace(GL_BACK);

    gl::viewport(0, 0, render_vars->window_width, render_vars->window_height);

    gl::clear_color(0.1f, 0.3f, 0.4f, 1.0f);

    render_vars->object_shader = Shader();
    render_vars->object_shader.add_shader_path(ShaderType::VERTEX,
                                               "object/object.vert");
    render_vars->object_shader.add_shader_path(
        ShaderType::FRAGMENT, "object/directional_light.frag",
        "object/point_light.frag", "object/object.frag");
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

    // Model test_model("models/cube/cube.obj");
    // models.emplace_back(std::move(test_model));

    auto planet         = std::make_unique<world::Planet>();
    render_vars->planet = std::move(planet);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return true;
}

void render(RenderVars *render_vars, uint64_t delta_time) {
    gl::clear(gl::BufferBit::COLOR | gl::BufferBit::DEPTH);

    render_vars->camera->apply_transformation();

    const auto  global_light_dir   = glm::vec3(-0.2f, -1.0f, -0.3f);
    const auto  global_light_color = glm::vec3(1.0f);
    const float luster             = 32.0f;
    // const float spotlight_angle    = glm::radians(12.5f);

    render_vars->object_shader.use();

    render_vars->object_shader.set_uniform_vec3f("u_ambient",
                                                 glm::vec3(0.2f, 0.2f, 0.2f));

    constexpr const char *name = "u_global_illumination";
    render_vars->object_shader.set_uniform_vec3f(
        name, "direction",
        util::to_viewspace(render_vars->camera->view(), global_light_dir,
                           0.0f));
    render_vars->object_shader.set_uniform_vec3f(name, "diffuse",
                                                 global_light_color / 2.0f);
    render_vars->object_shader.set_uniform_vec3f(name, "specular",
                                                 glm::vec3(1.0f));

    render_vars->object_shader.set_uniform_int("u_num_lights",
                                               point_lights.size());

    for (auto const &[index, point_light] :
         point_lights | std::views::enumerate) {
        const std::string &name = std::format("u_point_lights[{}]", index);
        render_vars->object_shader.set_uniform_vec3f(
            name, "position",
            util::to_viewspace(render_vars->camera->view(),
                               point_light.position, 1.0f));
        render_vars->object_shader.set_uniform_vec3f(name, "diffuse",
                                                     point_light.diffuse);
        render_vars->object_shader.set_uniform_vec3f(name, "specular",
                                                     point_light.specular);
        render_vars->object_shader.set_uniform_float(name, "constant",
                                                     point_light.constant);
        render_vars->object_shader.set_uniform_float(name, "linear",
                                                     point_light.linear);
        render_vars->object_shader.set_uniform_float(name, "quadratic",
                                                     point_light.quadratic);
    }

    render_vars->object_shader.set_uniform_mat4f("u_view",
                                                 render_vars->camera->view());

    float aspect_ratio = static_cast<float>(render_vars->window_width) /
                         render_vars->window_height;

    glm::mat4 projection =
        glm::perspective(glm::radians(75.0f), aspect_ratio, 0.1f, 100.0f);
    render_vars->object_shader.set_uniform_mat4f("u_projection", projection);

    render_vars->object_shader.set_uniform_mat4f("u_model", glm::mat4(1.0f));

    render_vars->object_shader.set_uniform_float("u_material0.luster", luster);
    for (const auto &[index, positions] : model_positions) {
        Model &model = models.at(index);
        for (const auto &position : positions) {
            auto model_space = glm::mat4(1.0f);
            model_space      = glm::translate(model_space, position);
            render_vars->object_shader.set_uniform_mat4f("u_model",
                                                         model_space);

            model.draw(render_vars->object_shader);
        }
    }

    auto model = glm::mat4(1.0f);
    glm::scale(model, glm::vec3(8.0f));
    glm::translate(model, glm::vec3(1.0f, 0.0f, -1.0f));
    render_vars->object_shader.set_uniform_mat4f("u_model", model);
    render_vars->planet->draw(render_vars->object_shader);

    render_vars->light_shader.use();

    render_vars->VAO->bind();

    render_vars->light_shader.set_uniform_mat4f("u_view",
                                                render_vars->camera->view());
    render_vars->light_shader.set_uniform_mat4f("u_projection", projection);

    for (const auto &point_light : point_lights) {
        render_vars->light_shader.set_uniform_vec3f("u_light_color",
                                                    point_light.specular);
        auto model = glm::mat4(1.0f);
        model      = glm::translate(model, point_light.position);
        model      = glm::scale(model, glm::vec3(0.2f));
        render_vars->light_shader.set_uniform_mat4f("u_model", model);

        gl::draw_arrays(gl::DrawMode::TRIANGLES, 0, 36);
    }
}

void quit() {}

}; // namespace render
