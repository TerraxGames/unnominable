#ifndef UNNOMINABLE_WORLD_PLANET_HPP_
#define UNNOMINABLE_WORLD_PLANET_HPP_
#include "../model.hpp"
#include <memory>
#include <vector>

namespace world {

struct PointVertex {
    glm::vec3 pos;
    glm::vec2 face_pos;
};

// https://www.binpress.com/creating-octahedron-sphere-unity/
class SphereMesh {
private:
    render::Mesh                       mesh_;
    std::unique_ptr<VertexArrayObject> vao;
    std::unique_ptr<BufferObject>      vbo;
    std::vector<PointVertex>           vertices;

public:
    SphereMesh(int resolution);

    const render::Mesh &mesh() const { return mesh_; }

    void draw_points() const;
};

class Planet {
public:
    world::SphereMesh sphere_mesh;

    Planet();

    void draw(const Shader &shader) const;
};

} // namespace world

#endif // UNNOMINABLE_WORLD_PLANET_HPP_
