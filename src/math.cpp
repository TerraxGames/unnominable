#include "math.hpp" // IWYU pragma: keep

namespace math {

glm::quat quatLookAt(const glm::vec3 &position, const glm::vec3 &target,
                     const glm::vec3 &up, const glm::vec3 &alternative_up) {
    glm::vec3 direction        = target - position;
    float     direction_length = glm::length(direction);

    // check if the direction is valid
    if (!(direction_length > 0.0001)) {
        return glm::quat(1, 0, 0, 0); // if not, return the identity
    }

    // normalize direction
    direction /= direction_length;

    if (glm::abs(glm::dot(direction, up)) > 0.9999f) {
        // use alternative up
        return glm::quatLookAt(direction, alternative_up);
    } else {
        return glm::quatLookAt(direction, up);
    }
}

/// gleans if the number is negative using C++ std and trig
/// if negative, returns -1
/// if positive, returns 1
float negative(const float &x) {
    return glm::cos(static_cast<float>(std::signbit(x)) * glm::pi<float>());
}

} // namespace math
