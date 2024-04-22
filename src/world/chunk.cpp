#include "chunk.hpp"

namespace world {

Chunk::Chunk() {
    this->data = std::array<int32_t, 4096>{};
    this->data.fill(-1);
}

} // namespace world
