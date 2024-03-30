#include "model.hpp"
#include "log.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <ranges>
#include <unordered_map>

namespace render {

std::unordered_map<std::string, Texture> loaded_textures{};

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices,
           std::vector<Texture> &textures) {
    this->vertices = vertices;
    this->indices  = indices;
    this->textures = textures;

    this->initialize_mesh();
}

void Mesh::initialize_mesh() {
    this->VAO = std::make_unique<VertexArrayObject>();
    this->VBO = std::make_unique<BufferObject>(BufferType::ARRAY);
    this->EBO = std::make_unique<BufferObject>(BufferType::ELEMENT_ARRAY);

    this->VAO->bind();
    this->VBO->bind();
    this->EBO->bind();

    this->VBO->upload_data(this->vertices, BufferUsage::STATIC_DRAW);

    this->EBO->upload_data(this->indices, BufferUsage::STATIC_DRAW);

    this->VAO->init_vbo(8, GLtype::FLOAT);
    this->VAO->attrib_pointer_f(3, false);
    this->VAO->enable_attrib_array();
    this->VAO->attrib_pointer_f(3, false);
    this->VAO->enable_attrib_array();
    this->VAO->attrib_pointer_f(2, false);
    this->VAO->enable_attrib_array();
}

void Mesh::draw(Shader &shader) {
    // bind textures
    int diffuse_index  = 0;
    int specular_index = 0;
    int emissive_index = 0;
    int other_index    = 0;
    for (const auto &[index, texture] :
         this->textures | std::views::enumerate) {
        texture.bind_active(get_texture_unit(index));

        switch (texture.type) {
        case TextureType::DIFFUSE:
            shader.set_uniform_int(
                std::format("u_material{}.diffuse", diffuse_index), index);
            diffuse_index++;
            break;
        case TextureType::SPECULAR:
            shader.set_uniform_int(
                std::format("u_material{}.specular", specular_index), index);
            specular_index++;
            break;
        case TextureType::EMISSIVE:
            shader.set_uniform_int(
                std::format("u_material{}.emissive", emissive_index), index);
            emissive_index++;
            break;
        case TextureType::MISC:
            shader.set_uniform_int(std::format("u_texture{}", other_index),
                                   index);
            other_index++;
            break;
        default:
            throw TextureLoadException(std::format("N/A (index #{})", index),
                                       "Unknown texture type!");
        }
    }

    // draw mesh
    this->VAO->bind();
    gl::draw_elements(gl::DrawMode::TRIANGLES, this->indices.size(),
                      GLtype::UNSIGNED_INT, nullptr);
    this->VAO->unbind();
}

void Model::load(const std::string &path) {
    this->parent_directory = path.substr(0, path.find_last_of('/'));

    Assimp::Importer importer{};
    const aiScene   *scene =
        importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (scene == nullptr || scene->mRootNode == nullptr ||
        scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        SDL_LogError(UN_LOG_CATEGORY_ASSIMP, "%s", importer.GetErrorString());
        return;
    }

    this->process_node(*scene->mRootNode, *scene);
}

void Model::process_node(const aiNode &node, const aiScene &scene) {
    for (int i = 0; i < node.mNumMeshes; i++) {
        const aiMesh &mesh = *scene.mMeshes[node.mMeshes[i]];
        this->meshes.emplace_back(this->process_mesh(mesh, scene));
    }

    for (int i = 0; i < node.mNumChildren; i++) {
        this->process_node(*node.mChildren[i], scene);
    }
}

Mesh Model::process_mesh(const aiMesh &mesh, const aiScene &scene) const {
    std::vector<Vertex>                                               vertices;
    std::vector<unsigned int /* hatsune miku save me, i've sinned */> indices;
    std::vector<Texture>                                              textures;

    for (int i = 0; i < mesh.mNumVertices; i++) {
        Vertex     vertex;
        aiVector3D position = mesh.mVertices[i];
        vertex.position     = glm::vec3(position.x, position.y, position.z);

        aiVector3D normal = mesh.mNormals[i];
        vertex.normal     = glm::vec3(normal.x, normal.y, normal.z);

        if (mesh.mTextureCoords[0] != nullptr) {
            aiVector3D texcoords = mesh.mTextureCoords[0][i];
            vertex.texcoords     = glm::vec2(texcoords.x, texcoords.y);
        } else {
            vertex.texcoords = glm::vec2(0.0f);
        }

        vertices.emplace_back(vertex);
    }

    for (int i = 0; i < mesh.mNumFaces; i++) {
        aiFace face = mesh.mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.emplace_back(face.mIndices[j]);
        }
    }

    if (mesh.mMaterialIndex >= 0) {
        const aiMaterial    &material = *scene.mMaterials[mesh.mMaterialIndex];
        std::vector<Texture> diffuse_maps =
            this->load_material_textures(material, TextureType::DIFFUSE);
        textures.insert(textures.end(), diffuse_maps.begin(),
                        diffuse_maps.end());

        std::vector<Texture> specular_maps =
            this->load_material_textures(material, TextureType::SPECULAR);
        textures.insert(textures.end(), specular_maps.begin(),
                        specular_maps.end());

        std::vector<Texture> emissive_maps =
            this->load_material_textures(material, TextureType::EMISSIVE);
        if (emissive_maps.size() == 0) {
            if (!loaded_textures.contains("textures/blank.jxl")) {
                ImageTexture texture("textures/blank.jxl");
                texture.type = TextureType::EMISSIVE;
                texture.bind_generate();
                texture.default_parameters();
                texture.upload();
                texture.generate_mipmap();
                texture.free_surface();
                loaded_textures.emplace("textures/blank.jxl", texture);
            }
            emissive_maps.emplace_back(
                loaded_textures.at("textures/blank.jxl"));
        }
        textures.insert(textures.end(), emissive_maps.begin(),
                        emissive_maps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture>
Model::load_material_textures(const aiMaterial &material,
                              TextureType       texture_type) const {
    std::vector<Texture> textures;
    for (int i = 0;
         i < material.GetTextureCount(static_cast<aiTextureType>(texture_type));
         i++) {
        aiString why_is_there_another_string_type;
        material.GetTexture(static_cast<aiTextureType>(texture_type), i,
                            &why_is_there_another_string_type);
        std::string path{this->parent_directory};
        path.push_back('/');
        path.append(why_is_there_another_string_type.C_Str());

        if (loaded_textures.contains(path)) {
            textures.emplace_back(loaded_textures.at(path));
            continue;
        }

        ImageTexture texture(path);
        texture.type = texture_type;
        texture.bind_generate();
        texture.default_parameters();
        texture.upload();
        texture.generate_mipmap();
        texture.free_surface();
        textures.emplace_back(texture);
        loaded_textures.emplace(path, texture);
    }

    return textures;
}

void Model::draw(Shader &shader) {
    for (auto &mesh : this->meshes) {
        mesh.draw(shader);
    }
}

} // namespace render
