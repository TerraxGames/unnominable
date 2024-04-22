#ifndef UNNOMINABLE_WORLD_PLANET_HPP_
#define UNNOMINABLE_WORLD_PLANET_HPP_
#include "../model.hpp"

namespace world {

// https://www.binpress.com/creating-octahedron-sphere-unity/
class SphereMesh {
private:
    render::Mesh mesh_;

public:
    SphereMesh(int resolution);

    const render::Mesh &mesh() const { return mesh_; }
};

class Planet {
public:
    world::SphereMesh sphere_mesh;

    Planet();

    void draw(const Shader &shader) const;
};

} // namespace world

#endif // UNNOMINABLE_WORLD_PLANET_HPP_
