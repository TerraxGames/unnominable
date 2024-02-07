#ifndef UNNOMINABLE_SHADER_HPP_
#define UNNOMINABLE_SHADER_HPP_
#include <concepts>
#include <cstdint>
#include <glad/gl.h>
#include <string>
#include <vector>
#include <map>

enum ShaderType {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

struct ShaderFilePath {
    ShaderType shader_type;
    std::vector<std::string> file_paths;
};

class Shader {
public:
    Shader();
    void add_shader_path(ShaderType shader_type, std::vector<const char *> const &file_paths_vector);
    void add_shader_path(ShaderType shader_type, std::convertible_to<const char *> auto ...file_paths) {
        std::vector<const char *> file_paths_vector = {file_paths...};
        add_shader_path(shader_type, file_paths_vector);
    }
    bool compile_and_link(); // todo: use exceptions
    void use();
    GLuint get_shader_program();
    void set_uniform_bool(const std::string &name, bool value);
    void set_uniform_int(const std::string &name, GLint value);
    void set_uniform_float(const std::string &name, GLfloat value);
private:
    std::map<ShaderType, GLuint> shader_objects;
    std::map<ShaderType, std::vector<const char *>> shader_paths;
    GLuint shader_program;
    GLint success;
    GLchar info_log[512];

    bool compile_shader_pipe(ShaderType shader_type);
};

#endif // UNNOMINABLE_SHADER_HPP_
