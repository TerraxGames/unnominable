#ifndef UNNOMINABLE_UTIL_HPP_
#define UNNOMINABLE_UTIL_HPP_

#include "objects.hpp"
#include "types.hpp"
#include <cstddef>
#include <string>
#include <utility>
namespace util {

/// Converts a GLtype_int to a GLtype.
constexpr GLtype from_gltype_int(GLtype_int type) {
    return GLtype{std::to_underlying(type)};
}

/// Calculates the size of a GLtype.
size_t sizeof_gltype(GLtype type);

} // namespace util

/// some wrappers for OpenGL :3
namespace gl {

enum class ObjectType : GLenum {
    BUFFER             = GL_BUFFER,
    SHADER             = GL_SHADER,
    PROGRAM            = GL_PROGRAM,
    VERTEX_ARRAY       = GL_VERTEX_ARRAY,
    QUERY              = GL_QUERY,
    PROGRAM_PIPELINE   = GL_PROGRAM_PIPELINE,
    TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK,
    SAMPLER            = GL_SAMPLER,
    TEXTURE            = GL_TEXTURE,
    RENDERBUFFER       = GL_RENDERBUFFER,
    FRAMEBUFFER        = GL_FRAMEBUFFER,
};

enum class DrawMode : GLenum {
    POINTS                   = GL_POINTS,
    LINE_STRIP               = GL_LINE_STRIP,
    LINE_LOOP                = GL_LINE_LOOP,
    LINES                    = GL_LINES,
    LINE_STRIP_ADJACENCY     = GL_LINE_STRIP_ADJACENCY,
    LINES_ADJACENCY          = GL_LINES_ADJACENCY,
    TRIANGLE_STRIP           = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN             = GL_TRIANGLE_FAN,
    TRIANGLES                = GL_TRIANGLES,
    TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
    TRIANGLES_ADJACENCY      = GL_TRIANGLES_ADJACENCY,
    PATCHES                  = GL_PATCHES,
};

inline void object_label(ObjectType identifier, GLobject object_name,
                         GLsizei length, const char *label) {
    glObjectLabel(std::to_underlying(identifier), object_name, length, label);
}

inline void object_label(ObjectType identifier, GLobject object_name,
                         const std::string &label) {
    object_label(identifier, object_name, label.size(), label.c_str());
}

inline void draw_elements(DrawMode mode, GLsizei count, GLtype type,
                          const GLvoid *indices) {
    glDrawElements(std::to_underlying(mode), count, std::to_underlying(type),
                   indices);
}

} // namespace gl

#endif // UNNOMINABLE_UTIL_HPP_
