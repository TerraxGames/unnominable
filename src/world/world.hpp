#ifndef UNNOMINABLE_WORLD_WORLD_HPP_
#define UNNOMINABLE_WORLD_WORLD_HPP_
#include "../math.hpp" // IWYU pragma: keep
#include <cstdint>

namespace world {

/// This is a position type used when rendering entities in the rendered world.
typedef glm::vec3 RenderPos;

/// A position of a quadrant.
/// Quadrants act like alternate universes in that each time a position
/// coordinate exceeds -1024.0f or 1024.0f, it becomes mod(coordinate, 1024.0f),
/// and the quadrant position is added with floor(coordinate / 1024.0f).
typedef glm::tvec3<int64_t> QuadrantPos;

/// This kind of position interacts with the world, and in turn, quadrants.
struct WorldPos {
    glm::vec3   vec;
    QuadrantPos quadrant;
};

} // namespace world

#endif // UNNOMINABLE_WORLD_WORLD_HPP_
