#ifndef UNNOMINABLE_SHADER_HPP_
#define UNNOMINABLE_SHADER_HPP_
#include <glad/gl.h>
#include <map>
#include <string>
#include <vector>

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
    std::map<ShaderType, GLuint>                   shader_objects;
    std::map<ShaderType, std::vector<std::string>> shader_paths;
    GLint                                          success;
    GLchar                                         info_log[512];

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

    bool compile_and_link(); // todo: use exceptions

    void use();

    void set_uniform_bool(const std::string &name, bool value);
    void set_uniform_int(const std::string &name, GLint value);
    void set_uniform_float(const std::string &name, GLfloat value);
};

#endif // UNNOMINABLE_SHADER_HPP_
