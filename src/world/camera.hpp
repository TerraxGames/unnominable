#ifndef UNNOMINABLE_WORLD_CAMERA_HPP_
#define UNNOMINABLE_WORLD_CAMERA_HPP_
#include "../math.hpp"
#include "world.hpp"

namespace world {

class Camera {
private:
    glm::mat4 view_    = glm::mat4(1.0f);
    glm::vec3 right_   = glm::vec3();
    glm::vec3 up_      = glm::vec3();
    glm::vec3 forward_ = glm::vec3();

public:
    RenderPos position    = glm::vec3(0.0f);
    glm::quat rotation    = glm::quat_identity<float, glm::defaultp>();
    float     pitch       = 0.0f;
    float     yaw         = 0.0f;
    float     sensitivity = 0.1f;

    Camera() = default;
    Camera(RenderPos position);

    inline constexpr void look_at(const RenderPos &target) {
        this->rotation = math::quatLookAt(
            this->position, target, math::Direction::UP,
            math::Direction::UP + glm::vec3(0.0f, 0.001f, 0.0f));
    }

    inline constexpr void look_at(const RenderPos &position,
                                  const RenderPos &target) {
        this->position = position;
        this->look_at(target);
    }

    void apply_transformation();

    const glm::mat4        &view() const { return this->view_; }
    const world::RenderPos &forward() const { return this->forward_; }
    const world::RenderPos &right() const { return this->right_; }
    const world::RenderPos &up() const { return this->up_; }
};

} // namespace world

#endif // UNNOMINABLE_WORLD_CAMERA_HPP_
