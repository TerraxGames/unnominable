#include "objects.hpp"
#include "util.hpp"
#include <utility>

BufferObject::BufferObject(BufferType type) {
    this->type_ = type;
    glGenBuffers(1, &this->object);
}

void BufferObject::bind() {
    glBindBuffer(std::to_underlying(this->type_), this->object);
}

void BufferObject::unbind() {
    glBindBuffer(std::to_underlying(this->type_), 0);
}

void BufferObject::upload_data(size_t size, const void *data,
                               BufferUsage usage) {
    glBufferData(std::to_underlying(this->type_), size, data,
                 std::to_underlying(usage));
}

void VertexArrayObject::unbind() { glBindVertexArray(0); }

VertexArrayObject::VertexArrayObject() { glGenVertexArrays(1, &this->object); }

void VertexArrayObject::bind() { glBindVertexArray(this->object); }

void VertexArrayObject::init_vbo(size_t row_size, GLtype type) {
    this->stride = row_size * util::sizeof_gltype(type);
    this->type   = type;
}

void VertexArrayObject::attrib_pointer_f(GLint size, bool normalized) {
    const void *offset = reinterpret_cast<const void *>(
        this->total_attrib_size * util::sizeof_gltype(this->type));
    glVertexAttribPointer(this->current_index, size,
                          std::to_underlying(this->type), normalized,
                          this->stride, offset);
    this->total_attrib_size += size;
    this->current_index++;
}

void VertexArrayObject::enable_attrib_array(GLuint index) {
    glEnableVertexAttribArray(index);
}

void VertexArrayObject::enable_attrib_array() {
    this->enable_attrib_array(this->current_index - 1);
}
