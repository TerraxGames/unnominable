#include "planet.hpp"
#include "../math.hpp" // IWYU pragma: keep
#include "../model.hpp"
#include <memory>
#include <SDL_log.h>

namespace world {

SphereMesh::SphereMesh(int resolution) {
    std::vector<PointVertex>    point_vertices{};
    std::vector<render::Vertex> vertices{};
    std::vector<unsigned int>   indices{};

    constexpr float one_third  = 1.0f / 3.0f;
    constexpr float two_thirds = 2.0f / 3.0f;

    // north face
    for (int x = 0; x <= resolution; x++) {
        float progress_x = static_cast<float>(x) / resolution;
        for (int y = 0; y <= resolution; y++) {
            // calculate & push vertex
            float progress_y = static_cast<float>(y) / resolution;
            float x_result   = glm::lerp(-1.0f, 1.0f, progress_x);
            float y_result   = glm::lerp(-1.0f, 1.0f, progress_y);
            auto  position   = glm::vec3(x_result, y_result, -1.0f);

            position                 = glm::normalize(position);
            PointVertex point_vertex = {
                .pos = position, .face_pos = glm::vec2(progress_x, progress_y)};
            point_vertices.emplace_back(point_vertex);

            auto texcoords = glm::vec2();
            texcoords.x    = glm::lerp(0.5f, 0.75f, progress_x);
            texcoords.y    = glm::lerp(one_third, two_thirds, progress_y);
            render::Vertex vertex = {.position  = position,
                                     .normal    = position,
                                     .texcoords = texcoords};
            vertices.emplace_back(vertex);
        }
    }

    for (int i = 1; i <= resolution * resolution + (resolution - 1); i++) {
        if (i % (resolution + 1) == 0) {
            // Apply hack if we're about to wrap behind.
            // If we don't do this, it will create a face on the back-side at
            // the wrong points.
            i++;
        }
        indices.emplace_back(i);
        indices.emplace_back(i + resolution);
        indices.emplace_back(i - 1);
    }

    // south face
    // for (int x = 0; x <= resolution; x++) {
    //     float progress_x = static_cast<float>(x) / resolution;
    //     for (int y = 0; y <= resolution; y++) {
    //         float progress_y = static_cast<float>(y) / resolution;
    //         float x_result   = glm::lerp(-1.0f, 1.0f, progress_x);
    //         float y_result   = glm::lerp(-1.0f, 1.0f, progress_y);
    //         auto  position   = glm::vec3(x_result, y_result, 1.0f);

    //         position = glm::normalize(position);
    //         point_vertices.emplace_back(glm::normalize(position));

    //         auto texcoords = glm::vec2();
    //         texcoords.x    = glm::lerp(0.0f, 0.25f, progress_x);
    //         texcoords.y    = glm::lerp(one_third, two_thirds, progress_y);
    //         render::Vertex vertex = {.position  = position,
    //                                  .normal    = position,
    //                                  .texcoords = texcoords};
    //         vertices.emplace_back(vertex);
    //     }
    // }

    // // east face
    // for (int z = 0; z <= resolution; z++) {
    //     float progress_z = static_cast<float>(z) / resolution;
    //     for (int y = 0; y <= resolution; y++) {
    //         float progress_y = static_cast<float>(y) / resolution;
    //         float y_result   = glm::lerp(-1.0f, 1.0f, progress_y);
    //         float z_result   = glm::lerp(-1.0f, 1.0f, progress_z);
    //         auto  position   = glm::vec3(1.0f, y_result, z_result);

    //         position = glm::normalize(position);
    //         point_vertices.emplace_back(position);

    //         auto texcoords        = glm::vec2();
    //         texcoords.x           = glm::lerp(0.25f, 0.5f, progress_z);
    //         texcoords.y           = glm::lerp(0.0f, one_third, progress_y);
    //         render::Vertex vertex = {.position  = position,
    //                                  .normal    = position,
    //                                  .texcoords = texcoords};
    //         vertices.emplace_back(vertex);
    //     }
    // }

    // // west face
    // for (int z = 0; z <= resolution; z++) {
    //     float progress_z = static_cast<float>(z) / resolution;
    //     for (int y = 0; y <= resolution; y++) {
    //         float progress_y = static_cast<float>(y) / resolution;
    //         float y_result   = glm::lerp(-1.0f, 1.0f, progress_y);
    //         float z_result   = glm::lerp(-1.0f, 1.0f, progress_z);
    //         auto  position   = glm::vec3(-1.0f, y_result, z_result);

    //         position = glm::normalize(position);
    //         point_vertices.emplace_back(position);

    //         auto texcoords        = glm::vec2();
    //         texcoords.x           = glm::lerp(0.25f, 0.5f, progress_z);
    //         texcoords.y           = glm::lerp(two_thirds, 1.0f, progress_y);
    //         render::Vertex vertex = {.position  = position,
    //                                  .normal    = position,
    //                                  .texcoords = texcoords};
    //         vertices.emplace_back(vertex);
    //     }
    // }

    // // top face
    // for (int x = 0; x <= resolution; x++) {
    //     float progress_x = static_cast<float>(x) / resolution;
    //     for (int z = 0; z <= resolution; z++) {
    //         float progress_z = static_cast<float>(z) / resolution;
    //         float x_result   = glm::lerp(-1.0f, 1.0f, progress_x);
    //         float z_result   = glm::lerp(-1.0f, 1.0f, progress_z);
    //         auto  position   = glm::vec3(x_result, 1.0f, z_result);

    //         position = glm::normalize(position);
    //         point_vertices.emplace_back(position);

    //         auto texcoords = glm::vec2();
    //         texcoords.x    = glm::lerp(0.25f, 0.5f, progress_x);
    //         texcoords.y    = glm::lerp(one_third, two_thirds, progress_z);
    //         render::Vertex vertex = {.position  = position,
    //                                  .normal    = position,
    //                                  .texcoords = texcoords};
    //         vertices.emplace_back(vertex);
    //     }
    // }

    // // bottom face
    // for (int x = 0; x <= resolution; x++) {
    //     float progress_x = static_cast<float>(x) / resolution;
    //     for (int z = 0; z <= resolution; z++) {
    //         float progress_z = static_cast<float>(z) / resolution;
    //         float x_result   = glm::lerp(-1.0f, 1.0f, progress_x);
    //         float z_result   = glm::lerp(-1.0f, 1.0f, progress_z);
    //         auto  position   = glm::vec3(x_result, -1.0f, z_result);

    //         position = glm::normalize(position);
    //         point_vertices.emplace_back(position);

    //         auto texcoords = glm::vec2();
    //         texcoords.x    = glm::lerp(0.75f, 1.0f, progress_x);
    //         texcoords.y    = glm::lerp(one_third, two_thirds, progress_z);
    //         render::Vertex vertex = {.position  = position,
    //                                  .normal    = position,
    //                                  .texcoords = texcoords};
    //         vertices.emplace_back(vertex);
    //     }
    // }

    // prepare point drawing
    this->vertices = point_vertices;
    this->vao      = std::make_unique<VertexArrayObject>();
    this->vao->bind();
    this->vbo = std::make_unique<BufferObject>(BufferType::ARRAY);
    this->vbo->bind();
    this->vbo->upload_data(this->vertices, BufferUsage::STATIC_DRAW);
    this->vao->init_vbo(5, GLtype::FLOAT);
    this->vao->attrib_pointer_f(3, false);
    this->vao->enable_attrib_array();
    this->vao->attrib_pointer_f(2, false);
    this->vao->enable_attrib_array();
    this->vbo->unbind();
    this->vao->unbind();

    // wrap UV
    this->mesh_          = render::Mesh();
    this->mesh_.vertices = vertices;
    this->mesh_.indices  = indices;
    auto texture         = ImageTexture("textures/dice_unwrap.png");
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
    gl::draw_arrays(gl::DrawMode::POINTS, 0, this->vertices.size());
    this->vao->unbind();
}

Planet::Planet() : sphere_mesh(world::SphereMesh(4)) {}

void Planet::draw(const Shader &shader) const {
    this->sphere_mesh.mesh().draw(shader);
}

} // namespace world
