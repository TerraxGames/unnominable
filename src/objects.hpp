#ifndef UNNOMINABLE_OBJECTS_HPP_
#define UNNOMINABLE_OBJECTS_HPP_
#include "glad/gl.h"
#include "types.hpp"
#include "util.hpp"
#include <array>
#include <cstddef>

/// The buffer target.
/// Quoth the wiki,
/// > The `target`​ defines how you intend to use this binding of the buffer
/// > object. When you're just creating, filling the buffer object with data, or
/// > both, the target you use doesn't technically matter.
/// https://www.khronos.org/opengl/wiki/Buffer_Object#Creation
enum class BufferType : GLenum {
    ARRAY              = GL_ARRAY_BUFFER,
    ATOMIC_COUNTER     = GL_ATOMIC_COUNTER_BUFFER,
    COPY_READ          = GL_COPY_READ_BUFFER,
    COPY_WRITE         = GL_COPY_WRITE_BUFFER,
    DISPATCH_INDIRECT  = GL_DISPATCH_INDIRECT_BUFFER,
    DRAW_INDIRECT      = GL_DRAW_INDIRECT_BUFFER,
    ELEMENT_ARRAY      = GL_ELEMENT_ARRAY_BUFFER,
    PIXEL_PACK         = GL_PIXEL_PACK_BUFFER,
    PIXEL_UNPACK       = GL_PIXEL_UNPACK_BUFFER,
    QUERY              = GL_QUERY_BUFFER,
    SHADER_STORAGE     = GL_SHADER_STORAGE_BUFFER,
    TEXTURE            = GL_TEXTURE_BUFFER,
    TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER,
    UNIFORM            = GL_UNIFORM_BUFFER,
};

/// Describes how the buffer will be used.
/// https://www.khronos.org/opengl/wiki/Buffer_Object#Buffer_Object_Usage
enum class BufferUsage : GLenum {
    STREAM_DRAW  = GL_STREAM_DRAW,
    STREAM_READ  = GL_STREAM_READ,
    STREAM_COPY  = GL_STREAM_COPY,
    STATIC_DRAW  = GL_STATIC_DRAW,
    STATIC_READ  = GL_STATIC_READ,
    STATIC_COPY  = GL_STATIC_COPY,
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    DYNAMIC_READ = GL_DYNAMIC_READ,
    DYNAMIC_COPY = GL_DYNAMIC_COPY,
};

/// A Buffer Object.
/// https://www.khronos.org/opengl/wiki/Buffer_Object
class BufferObject {
private:
    BufferType type_;

public:
    GLobject object;

    BufferObject(BufferType type);

    /// Bind the buffer object using glBindBuffer.
    void bind();

    /// Unbinds the current buffer object.
    void unbind();

    /// Upload buffer data to the GPU.
    void upload_data(size_t size, const void *data, BufferUsage usage);
    /// Upload buffer data to the GPU.
    template <typename T, size_t N>
    void upload_data(const std::array<T, N> &data, BufferUsage usage) {
        this->upload_data(N * sizeof(T), data.data(), usage);
    }

    const BufferType &type() const { return type_; }
};

/// A so-called VAO (Vertex Array Object).
/// https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object
class VertexArrayObject {
public:
    GLobject object;
    /// The stride of the currently-bound VBO.
    size_t   stride;
    /// The type of the currently-bound VBO.
    GLtype   type;
    /// The total size of the attributes added thus far.
    GLint    total_attrib_size{};
    /// The current index.
    GLuint   current_index{};

    /// Unbind the currently-bound VAO.
    static void unbind();

    /// Constructs a new VertexArrayObject and calls glGenVertexArrays.
    VertexArrayObject();

    /// Bind the VAO using glBindVertexArray.
    void bind();

    /// Sets the current VBO's type and row size.
    void init_vbo(size_t row_size, GLtype type);

    /// Define an attribute pointer using glVertexAttribPointer.
    void attrib_pointer_f(GLint size, bool normalized);

    /// Enable vertex attribute array access using glEnableVertexAttribArray.
    static inline void enable_attrib_array(GLuint index) {
        gl::enable_vertex_attrib_array(index);
    }
    /// Enable vertex attribute array access using glEnableVertexAttribArray.
    void enable_attrib_array();
};

#endif // UNNOMINABLE_OBJECTS_HPP_
