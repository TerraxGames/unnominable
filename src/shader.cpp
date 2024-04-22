#include "shader.hpp"
#include "types.hpp"
#include "util.hpp"
#include <algorithm> // IWYU pragma: keep  //required for bits/ranges_algo.h
#include <bits/ranges_algo.h>
#include <fstream>
#include <map>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <SDL.h>
#include <SDL_log.h>

Shader::Shader() {
    this->shader_objects = std::map<ShaderType, std::vector<GLobject>>();
    this->shader_paths   = std::map<ShaderType, std::vector<std::string>>();
}

void Shader::add_shader_path(
    ShaderType shader_type, std::vector<std::string> const &file_paths_vector) {
    this->shader_paths.emplace(shader_type, file_paths_vector);
}

void Shader::compile_and_link() {
    this->shader_program = glCreateProgram();

    auto keys = std::views::keys(this->shader_paths);
    for (const auto shader_type : keys) {
        if (!this->compile_shader_pipe(shader_type)) {
            throw std::runtime_error("Shader compilation failed!");
        }
        for (GLobject shader_object : this->shader_objects.at(shader_type)) {
            glAttachShader(this->shader_program, shader_object);
        }
    }

    glLinkProgram(this->shader_program);
    glGetProgramiv(this->shader_program, GL_LINK_STATUS, &this->success);
    if (!this->success) {
        glGetProgramInfoLog(this->shader_program, INFO_LOG_SIZE, NULL,
                            this->info_log);
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER,
                        "Shader program linking failed:\n%s", this->info_log);
        throw std::runtime_error("Shader linking failed!");
    }

    for (const auto &pair : this->shader_objects) {
        for (const GLobject shader_object : pair.second) {
            gl::delete_shader(shader_object);
        }
    }

    this->shader_objects.clear();
}

void Shader::use() { glUseProgram(this->shader_program); }

GLuint Shader::get_uniform_loc(const std::string &name) const {
    return glGetUniformLocation(this->shader_program, name.c_str());
}

void Shader::set_uniform_bool(const std::string &name, bool value) const {
    glUniform1i(this->get_uniform_loc(name), static_cast<GLint>(value));
}

void Shader::set_uniform_int(const std::string &name, GLint value) const {
    glUniform1i(this->get_uniform_loc(name), value);
}

void Shader::set_uniform_float(const std::string &name, GLfloat value) const {
    glUniform1f(this->get_uniform_loc(name), value);
}

void Shader::set_uniform_mat4f(const std::string &name,
                               const glm::mat4   &value) const {
    glUniformMatrix4fv(this->get_uniform_loc(name), 1, GL_FALSE,
                       glm::value_ptr(value));
}

void Shader::set_uniform_vec3f(const std::string &name,
                               const glm::vec3   &value) const {
    glUniform3fv(this->get_uniform_loc(name), 1, glm::value_ptr(value));
}

void Shader::set_uniform_vec4f(const std::string &name,
                               const glm::vec4   &value) const {
    glUniform4fv(this->get_uniform_loc(name), 1, glm::value_ptr(value));
}

bool Shader::compile_shader_pipe(ShaderType shader_type) {
    const std::vector<std::string> &shader_paths =
        this->shader_paths.at(shader_type);
    std::string shader_strs[shader_paths.size()]; // todo: use std::array

    for (int i = 0; i < shader_paths.size(); i++) {
        std::string file_path;
        file_path += "shaders/";
        file_path += shader_paths.at(i);

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

    this->shader_objects.emplace(shader_type, std::vector<GLobject>());

    for (int i = 0; i < shader_paths.size(); i++) {
        GLobject shader_object =
            glCreateShader(std::to_underlying(shader_type));
        std::vector<GLobject> &shader_objects =
            this->shader_objects.at(shader_type);
        shader_objects.emplace_back(shader_object);

        // set label
        gl::object_label(gl::ObjectType::SHADER, shader_object,
                         shader_paths.at(i));

        const char *shader_str = shader_strs[i].c_str();

        // compile shader
        glShaderSource(shader_object, 1, &shader_str, NULL);
        glCompileShader(shader_object);

        glGetShaderiv(shader_object, GL_COMPILE_STATUS, &this->success);
        if (!this->success) {
            glGetShaderInfoLog(shader_object, INFO_LOG_SIZE, NULL,
                               this->info_log);
            SDL_LogCritical(SDL_LOG_CATEGORY_RENDER,
                            "Shader compilation failed:\n%s", this->info_log);
            return false;
        }
    }

    return true;
}
