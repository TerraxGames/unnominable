#include "camera.hpp"

namespace world {

Camera::Camera(RenderPos position) : position(position) {}

void Camera::apply_transformation() {
    this->view_ = glm::translate(glm::mat4(1.0f) * glm::toMat4(this->rotation),
                                 -this->position);

    // https://stackoverflow.com/a/53612264/11774699
    const glm::mat4 inverted = glm::inverse(this->view_);
    this->forward_           = glm::normalize(glm::vec3(inverted[2]));

    this->right_ =
        glm::normalize(glm::cross(math::Direction::UP, this->forward_));
    this->up_ = glm::normalize(glm::cross(this->forward_, this->right_));
}

} // namespace world
