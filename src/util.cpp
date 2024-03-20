#include "util.hpp"

namespace util {

size_t sizeof_gltype(GLtype type) {
    switch (type) {
    case GLtype::BYTE:
    case GLtype::UNSIGNED_BYTE:
        return sizeof(GLbyte);
    case GLtype::SHORT:
    case GLtype::UNSIGNED_SHORT:
        return sizeof(GLshort);
    case GLtype::INT:
    case GLtype::INT_2_10_10_10_REV:
    case GLtype::UNSIGNED_INT:
    case GLtype::UNSIGNED_INT_2_10_10_10_REV:
    case GLtype::UNSIGNED_INT_10F_11F_11F_REV:
        return sizeof(GLint);
    case GLtype::FLOAT:
        return sizeof(GLfloat);
    case GLtype::DOUBLE:
        return sizeof(GLdouble);
    case GLtype::FIXED:
        return sizeof(GLfixed);
    case GLtype::HALF_FLOAT:
        return sizeof(GLhalf);
    }
}

glm::vec3 to_viewspace(glm::mat4 view, glm::vec3 position, float is_position) {
    return glm::vec3(view * glm::vec4(position, is_position));
}

} // namespace util

namespace gl {}
