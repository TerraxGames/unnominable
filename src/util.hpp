#ifndef UNNOMINABLE_UTIL_HPP_
#define UNNOMINABLE_UTIL_HPP_
#include "glad/gl.h"

namespace util {

template <class E>
constexpr GLenum to_glenum(E &value) {
    return static_cast<GLenum>(value);
};
template <class E>
constexpr const GLenum to_glenum(const E &value) {
    return static_cast<GLenum>(value);
};

} // namespace util

#endif // UNNOMINABLE_UTIL_HPP_
