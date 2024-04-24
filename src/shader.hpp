#ifndef UNNOMINABLE_SHADER_HPP_
#define UNNOMINABLE_SHADER_HPP_
#include "glm/ext/vector_float3.hpp"
#include "math.hpp" // IWYU pragma: keep
#include "types.hpp"
#include <format>
#include <glad/gl.h>
#include <map>
#include <string>
#include <vector>

#define INFO_LOG_SIZE 2048

enum class ShaderType : GLenum {
    VERTEX   = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

struct ShaderFilePath {
    ShaderType               shader_type;
    std::vector<std::string> file_paths;
};

class Shader {
private:
    std::map<ShaderType, std::vector<GLobject>>    shader_objects;
    std::map<ShaderType, std::vector<std::string>> shader_paths;
    GLint                                          success;
    GLchar                                         info_log[INFO_LOG_SIZE];

    bool compile_shader_pipe(ShaderType shader_type);

public:
    GLuint shader_program;

    Shader();

    void add_shader_path(ShaderType                      shader_type,
                         std::vector<std::string> const &file_paths_vector);
    void add_shader_path(ShaderType shader_type,
                         std::convertible_to<std::string> auto... file_paths) {
        std::vector<std::string> file_paths_vector = {file_paths...};
        add_shader_path(shader_type, file_paths_vector);
    }

    void compile_and_link(); // todo: use exceptions

    void use() const;

    GLuint get_uniform_loc(const std::string &name) const;

    void set_uniform_bool(const std::string &name, bool value) const;
    void set_uniform_int(const std::string &name, GLint value) const;
    void set_uniform_float(const std::string &name, GLfloat value) const;
    void set_uniform_mat4f(const std::string &name,
                           const glm::mat4   &value) const;
    void set_uniform_vec3f(const std::string &name,
                           const glm::vec3   &value) const;
    void set_uniform_vec4f(const std::string &name,
                           const glm::vec4   &value) const;

    constexpr void set_uniform_bool(const std::string &parent,
                                    const std::string &name, bool value) {
        set_uniform_bool(std::format("{}.{}", parent, name), value);
    }
    constexpr void set_uniform_int(const std::string &parent,
                                   const std::string &name, GLint value) {
        set_uniform_int(std::format("{}.{}", parent, name), value);
    }
    constexpr void set_uniform_float(const std::string &parent,
                                     const std::string &name, GLfloat value) {
        set_uniform_float(std::format("{}.{}", parent, name), value);
    }
    constexpr void set_uniform_mat4f(const std::string &parent,
                                     const std::string &name,
                                     const glm::mat4   &value) {
        set_uniform_mat4f(std::format("{}.{}", parent, name), value);
    }
    constexpr void set_uniform_vec3f(const std::string &parent,
                                     const std::string &name,
                                     const glm::vec3   &value) {
        set_uniform_vec3f(std::format("{}.{}", parent, name), value);
    }
    constexpr void set_uniform_vec4f(const std::string &parent,
                                     const std::string &name,
                                     const glm::vec4   &value) {
        set_uniform_vec4f(std::format("{}.{}", parent, name), value);
    }
};

#endif // UNNOMINABLE_SHADER_HPP_
