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

} // namespace util

namespace gl {}
