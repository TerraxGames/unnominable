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
    float     sensitivity = 0.1f;

    Camera() = default;
    Camera(RenderPos position);

    inline constexpr void look_at(const RenderPos &target) {
        this->rotation = math::quatLookAt(
            this->position, target, math::Direction::UP,
            math::Direction::UP + glm::vec3(0.0f, 0.001f, 0.0f));

        // i have no fucking clue why this makes it work, but it does, so...
        this->position = this->position * this->rotation;
    }

    inline constexpr void look_at(const RenderPos &position,
                                  const RenderPos &target) {
        this->position = position;
        this->look_at(target);
    }

    inline constexpr void look_forward() {
        this->look_at(math::Direction::NORTH);
    }

    inline constexpr void apply_transformation() {
        this->view_ = glm::translate(
            glm::mat4(1.0f) * glm::toMat4(this->rotation), -this->position);

        // https://stackoverflow.com/a/53612264/11774699
        const glm::mat4 inverted = glm::inverse(this->view_);
        this->forward_           = glm::normalize(glm::vec3(inverted[2]));

        this->right_ =
            glm::normalize(glm::cross(math::Direction::UP, this->forward_));
        this->up_ = glm::normalize(glm::cross(this->forward_, this->right_));
    }

    const glm::mat4        &view() const { return this->view_; }
    const world::RenderPos &forward() const { return this->forward_; }
    const world::RenderPos &right() const { return this->right_; }
    const world::RenderPos &up() const { return this->up_; }
};

} // namespace world

#endif // UNNOMINABLE_WORLD_CAMERA_HPP_
