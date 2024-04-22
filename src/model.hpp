#ifndef UNNOMINABLE_MODEL_HPP_
#define UNNOMINABLE_MODEL_HPP_
#include "math.hpp" // IWYU pragma: keep
#include "objects.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include <assimp/material.h>
#include <assimp/scene.h>
#include <initializer_list>
#include <memory>

namespace render {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoords;

    Vertex() {}
    Vertex(std::initializer_list<float> list)
        : position(list.begin()[0], list.begin()[1], list.begin()[2]),
          normal(list.begin()[3], list.begin()[4], list.begin()[5]),
          texcoords(list.begin()[6], list.begin()[7]) {}
};
// ask the compiler to pretty please reject this type if its largest
// primitive isn't 4 bytes
static_assert(alignof(Vertex) == alignof(float));

class Mesh {
private:
    std::unique_ptr<VertexArrayObject> VAO;
    std::unique_ptr<BufferObject>      VBO, EBO;

public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    bool                      draw_elements = true;

    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices,
         std::vector<Texture> &textures);
    Mesh();

    void initialize_mesh();
    void draw(const Shader &shader) const;
};

class Model {
public:
    Model(const std::string &path) { load(path); }

    void draw(const Shader &shader) const;

    const std::vector<Mesh> &meshes() const { return meshes_; }

private:
    std::vector<Mesh> meshes_;
    std::string       parent_directory;

    void load(const std::string &path);
    void process_node(const aiNode &node, const aiScene &scene);
    Mesh process_mesh(const aiMesh &mesh, const aiScene &scene) const;
    std::vector<Texture> load_material_textures(const aiMaterial &material,
                                                TextureType texture_type) const;
};

} // namespace render

#endif // UNNOMINABLE_MODEL_HPP_