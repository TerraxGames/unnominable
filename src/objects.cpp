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

void VertexArrayObject::unbind() { gl::bind_vertex_array(0); }

VertexArrayObject::VertexArrayObject() { glGenVertexArrays(1, &this->object); }

void VertexArrayObject::bind() { gl::bind_vertex_array(this->object); }

void VertexArrayObject::init_vbo(size_t row_size, GLtype type) {
    this->stride = row_size * util::sizeof_gltype(type);
    this->type   = type;
}

void VertexArrayObject::attrib_pointer_f(GLint size, bool normalized) {
    size_t offset = this->total_attrib_size * util::sizeof_gltype(this->type);
    gl::vertex_attrib_pointer(this->current_index, size, this->type, normalized,
                              this->stride, offset);
    this->total_attrib_size += size;
    this->current_index++;
}

void VertexArrayObject::enable_attrib_array() {
    this->enable_attrib_array(this->current_index - 1);
}
