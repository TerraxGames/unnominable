#ifndef UNNOMINABLE_MATH_HPP_
#define UNNOMINABLE_MATH_HPP_

#define GLM_FORCE_SWIZZLE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/common.hpp>               // IWYU pragma: keep
#include <glm/ext/matrix_transform.hpp> // IWYU pragma: keep
#include <glm/fwd.hpp>                  // IWYU pragma: keep
#include <glm/geometric.hpp>            // IWYU pragma: keep
#include <glm/glm.hpp>                  // IWYU pragma: keep
#include <glm/gtc/matrix_transform.hpp> // IWYU pragma: keep
#include <glm/gtc/quaternion.hpp>       // IWYU pragma: keep
#include <glm/gtc/type_ptr.hpp>         // IWYU pragma: keep
#include <glm/gtx/quaternion.hpp>       // IWYU pragma: keep
#include <glm/trigonometric.hpp>        // IWYU pragma: keep

namespace math {

class Direction {
public:
    static constexpr glm::vec3 EAST  = glm::vec3(1.0f, 0.0f, 0.0f);
    static constexpr glm::vec3 WEST  = glm::vec3(-1.0f, 0.0f, 0.0f);
    static constexpr glm::vec3 UP    = glm::vec3(0.0f, 1.0f, 0.0f);
    static constexpr glm::vec3 DOWN  = glm::vec3(0.0f, -1.0f, 0.0f);
    static constexpr glm::vec3 NORTH = glm::vec3(0.0f, 0.0f, -1.0f);
    static constexpr glm::vec3 SOUTH = glm::vec3(0.0f, 0.0f, 1.0f);
};

#define col_type glm::mat<4, 4, T, Q>::col_type
template <typename T, glm::qualifier Q>
GLM_FUNC_QUALIFIER GLM_CONSTEXPR glm::mat<4, 4, T, Q> identity(T x, T y, T z,
                                                               T w) {
    return glm::mat<4, 4, T, Q>::mat(col_type(x, 0, 0, 0), //
                                     col_type(0, y, 0, 0), //
                                     col_type(0, 0, z, 0), //
                                     col_type(0, 0, 0, w));
}
#undef col_type

#define col_type glm::mat4::col_type
#define value_type glm::mat4::value_type
GLM_FUNC_QUALIFIER GLM_CONSTEXPR glm::mat4
identity(value_type x, value_type y, value_type z, value_type w) {
    return glm::mat4(col_type(x, 0, 0, 0), //
                     col_type(0, y, 0, 0), //
                     col_type(0, 0, z, 0), //
                     col_type(0, 0, 0, w));
}
#undef col_type
#undef value_type

/// origin of this magic: https://stackoverflow.com/a/49824672/11774699
glm::quat quatLookAt(const glm::vec3 &position, const glm::vec3 &target,
                     const glm::vec3 &up, const glm::vec3 &alternative_up);

float negative(const float &x);

} // namespace math

#endif // UNNOMINABLE_MATH_HPP_
