#ifndef UNNOMINABLE_WORLD_CHUNK_HPP_
#define UNNOMINABLE_WORLD_CHUNK_HPP_

#include <array>
#include <cstdint>
namespace world {

/// The chunk's position relative to the planet.
struct ChunkPos {
    int32_t x;
    int32_t y;
};

class Chunk {
public:
    std::array<int32_t, 4096> data;

    Chunk();
};

} // namespace world

#endif // UNNOMINABLE_WORLD_CHUNK_HPP_
