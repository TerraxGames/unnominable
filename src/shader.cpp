#include "shader.hpp"
#include "util.hpp"
#include <algorithm> // IWYU pragma: keep  //required for bits/ranges_algo.h
#include <bits/ranges_algo.h>
#include <fstream>
#include <functional>
#include <map>
#include <ranges>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <SDL.h>
#include <SDL_log.h>

Shader::Shader() {
    this->shader_objects = std::map<ShaderType, GLuint>();
    this->shader_paths   = std::map<ShaderType, std::vector<std::string>>();
}

void Shader::add_shader_path(
    ShaderType shader_type, std::vector<std::string> const &file_paths_vector) {
    this->shader_paths.emplace(shader_type, file_paths_vector);
}

bool Shader::compile_and_link() {
    this->shader_program = glCreateProgram();

    auto keys = std::views::keys(this->shader_paths);
    for (const auto shader_type : keys) {
        if (!this->compile_shader_pipe(shader_type)) {
            return false;
        }
        glAttachShader(this->shader_program,
                       this->shader_objects.at(shader_type));
    }

    glLinkProgram(this->shader_program);
    glGetProgramiv(this->shader_program, GL_LINK_STATUS, &this->success);
    if (!this->success) {
        glGetProgramInfoLog(this->shader_program, 512, NULL, this->info_log);
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER,
                        "Shader program linking failed:\n%s", this->info_log);
        return false;
    }

    for (const auto &pair : this->shader_objects) {
        glDeleteShader(pair.second);
    }

    this->shader_objects.clear();
    return true;
}

void Shader::use() { glUseProgram(this->shader_program); }

void Shader::set_uniform_bool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(this->shader_program, name.c_str()),
                static_cast<int>(value));
}

void Shader::set_uniform_int(const std::string &name, GLint value) {
    glUniform1i(glGetUniformLocation(this->shader_program, name.c_str()),
                value);
}

void Shader::set_uniform_float(const std::string &name, GLfloat value) {
    glUniform1f(glGetUniformLocation(this->shader_program, name.c_str()),
                value);
}

bool Shader::compile_shader_pipe(ShaderType shader_type) {
    const std::vector<std::string> &shader_paths =
        this->shader_paths.at(shader_type);
    std::string shader_strs[shader_paths.size()]; // todo: use std::array

    for (int i = 0; i < shader_paths.size(); i++) {
        std::string file_path;
        file_path += "shaders/";
        file_path += shader_paths[i];

        // https://stackoverflow.com/a/2602060/11774699
        std::ifstream shader_file(file_path);
        if (shader_file.fail()) {
            SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to find shader %s",
                         file_path.c_str());
            continue;
        }
        std::stringstream shader_buffer;
        shader_buffer << shader_file.rdbuf();
        std::string shader_str = shader_buffer.str();

        shader_strs[i] = shader_str;
    }

    const GLchar *shader_srcs[shader_paths.size()]; // todo: use std::array
    for (int i = 0; i < shader_paths.size(); i++) {
        std::string *shader_str = &shader_strs[i];
        shader_srcs[i]          = shader_str->c_str();
    }

    GLuint shader_object = glCreateShader(std::to_underlying(shader_type));
    this->shader_objects.emplace(shader_type, shader_object);

    // set label
    const std::string delim = ", ";
    const auto        label =
        std::ranges::fold_left(shader_paths | std::views::join_with(delim),
                               std::string{}, std::plus<>{});
    gl::object_label(gl::ObjectType::SHADER, shader_object, label);

    // compile shader
    glShaderSource(shader_object, shader_paths.size(), shader_srcs, NULL);
    glCompileShader(shader_object);

    glGetShaderiv(shader_object, GL_COMPILE_STATUS, &this->success);
    if (!this->success) {
        glGetShaderInfoLog(shader_object, 512, NULL, this->info_log);
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER,
                        "Shader compilation failed:\n%s", this->info_log);
        return false;
    }

    return true;
}
