#include "math.hpp" // IWYU pragma: keep
#include "glm/ext/quaternion_common.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/quaternion_transform.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"

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

} // namespace math
