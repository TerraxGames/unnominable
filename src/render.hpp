#ifndef UNNOMINABLE_RENDER_HPP_
#define UNNOMINABLE_RENDER_HPP_

#include "objects.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "world/camera.hpp"
#include <glad/gl.h>
#include <memory>

namespace render {

struct RenderVars {
    int      window_width  = 1280;
    int      window_height = 720;
    bool     should_quit   = false;
    uint32_t window_id;

    Shader object_shader;
    Shader light_shader;

    std::unique_ptr<world::Camera> camera;
    static constexpr float         camera_speed = 0.005f;

    std::unique_ptr<ImageTexture> container_tex;
    std::unique_ptr<ImageTexture> container_specular_tex;
    std::unique_ptr<ImageTexture> emissive_tex;

    GLint  success;
    GLchar info_log[512];

    std::unique_ptr<VertexArrayObject> VAO;
    std::unique_ptr<BufferObject>      VBO, EBO;
};

struct PointLight {
    glm::vec3 position;

    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoords;
};
// ask the compiler to pretty please reject this type if its largest
// primitive isn't 4 bytes
static_assert(alignof(Vertex) == alignof(float));

class Mesh {
private:
    std::unique_ptr<VertexArrayObject> VAO;
    std::unique_ptr<BufferObject>      VBO, EBO;

    void initialize_mesh();

public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices,
         std::vector<Texture> &textures);

    void draw(Shader &shader);
};

bool init(RenderVars *render_vars);

void render(RenderVars *render_vars, uint64_t delta_time);

void quit();

}; // namespace render

#endif // UNNOMINABLE_RENDER_HPP_
