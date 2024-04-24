#include "planet.hpp"
#include "../math.hpp" // IWYU pragma: keep
#include "../model.hpp"
#include <memory>

namespace world {

SphereMesh::SphereMesh(int resolution) {
    std::vector<glm::vec3>    vertices{};
    std::vector<unsigned int> indices{};

    // bottom west-east edge
    for (int x = 0; x < resolution; x++) {
        float progress_x = static_cast<float>(x) / resolution;
        for (int y = 0; y < resolution; y++) {
            float progress_y = static_cast<float>(x) / resolution - 1.0f;
            vertices.emplace_back(glm::lerp(glm::vec3(-1.0f, progress_y, -1.0f),
                                            glm::vec3(1.0f, progress_y, -1.0f),
                                            progress_x));
        }
    }

    // prepare point drawing
    this->vertices = vertices;
    this->vao      = std::make_unique<VertexArrayObject>();
    this->vao->bind();
    this->vbo = std::make_unique<BufferObject>(BufferType::ARRAY);
    this->vbo->bind();
    this->vbo->upload_data(this->vertices, BufferUsage::STATIC_DRAW);
    this->vao->init_vbo(3, GLtype::FLOAT);
    this->vao->attrib_pointer_f(3, false);
    this->vao->enable_attrib_array();
    this->vbo->unbind();
    this->vao->unbind();

    // wrap UV
    this->mesh_         = render::Mesh();
    this->mesh_.indices = indices;
    auto texture        = ImageTexture("textures/uv-test.png");
    texture.bind_generate();
    texture.default_parameters();
    texture.upload();
    texture.generate_mipmap();
    texture.free_surface();
    this->mesh_.textures.emplace_back(texture);

    // horizontally flip UV
    for (auto &vertex : this->mesh_.vertices) {
        vertex.texcoords.x = -vertex.texcoords.x + 1;
    }

    this->mesh_.initialize_mesh();
}

void SphereMesh::draw_points() const {
    this->vao->bind();
    gl::draw_arrays(gl::DrawMode::POINTS, 0, this->vertices.size() * 3);
    this->vao->unbind();
}

Planet::Planet() : sphere_mesh(world::SphereMesh(3)) {}

void Planet::draw(const Shader &shader) const {
    this->sphere_mesh.mesh().draw(shader);
}

} // namespace world
