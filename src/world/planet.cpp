#include "planet.hpp"
#include "../math.hpp" // IWYU pragma: keep
#include "../model.hpp"

namespace world {

SphereMesh::SphereMesh(int resolution) {
    size_t vertex_count =
        4 * glm::pow((resolution + 1), 2) - 3 * (2 * resolution - 1);
    size_t index_count = glm::pow(2, 2 * resolution + 3) * 3;

    std::vector<glm::vec3> vertices{};
    vertices.reserve(vertex_count);
    std::vector<unsigned int> indices{};
    indices.reserve(index_count);

    for (int i = 0; i < 4; i++) {
        vertices.emplace_back(math::Direction::DOWN);
    }

    for (int i = 1; i <= resolution; i++) {
        float current_slice = static_cast<float>(i) / resolution;
        vertices.emplace_back(glm::lerp(
            math::Direction::DOWN, math::Direction::FORWARD, current_slice));
    }

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
    float previous_x = 1.0f;
    for (const auto &position : vertices) {
        auto vertex     = render::Vertex{};
        vertex.position = position;
        vertex.normal   = glm::normalize(vertex.position);
        // if we passed a seam and started a new triangle row, set previous to
        // right seam
        if (vertex.position.x == previous_x) {
            this->mesh_.vertices.at(this->mesh_.vertices.size() - 1)
                .texcoords.x = 1.0f;
        }
        previous_x = vertex.position.x;
        vertex.texcoords =
            glm::vec2(glm::atan(vertex.position.x, vertex.position.z) /
                          (-2.0f * glm::pi<float>()),
                      glm::asin(vertex.position.y) / glm::pi<float>() + 0.5f);
        if (vertex.texcoords.x < 0.0f) {
            vertex.texcoords.x += 1.0f;
        }
        this->mesh_.vertices.emplace_back(vertex);
    }

    // fix pole twisting
    this->mesh_.vertices.at(this->mesh_.vertices.size() - 4).texcoords.x =
        0.125f;
    this->mesh_.vertices.at(0).texcoords.x = 0.125f;
    this->mesh_.vertices.at(this->mesh_.vertices.size() - 3).texcoords.x =
        0.375f;
    this->mesh_.vertices.at(1).texcoords.x = 0.375f;
    this->mesh_.vertices.at(this->mesh_.vertices.size() - 2).texcoords.x =
        0.625f;
    this->mesh_.vertices.at(2).texcoords.x = 0.625f;
    this->mesh_.vertices.at(this->mesh_.vertices.size() - 1).texcoords.x =
        0.875f;
    this->mesh_.vertices.at(3).texcoords.x = 0.875f;

    // horizontally flip UV
    for (auto &vertex : this->mesh_.vertices) {
        vertex.texcoords.x = -vertex.texcoords.x + 1;
    }

    this->mesh_.initialize_mesh();
}

Planet::Planet() : sphere_mesh(world::SphereMesh(0)) {}

void Planet::draw(const Shader &shader) const {
    this->sphere_mesh.mesh().draw(shader);
}

} // namespace world
