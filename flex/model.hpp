#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <flex/config.hpp>
#include <flex/gl/texture.hpp>
#include <flex/mesh.hpp>
#include <memory>
#include <string>
#include <vector>

namespace flex {
class Model {
public:
  Model(std::string path);
  ~Model();

  void draw(gl::Shader &shader);

private:
  std::vector<std::shared_ptr<Mesh>> m_meshes;
  std::string m_directory;
  std::vector<std::shared_ptr<gl::Texture>>
      m_textures_loaded; // for optimization purposes

  void process_node(aiNode *node, const aiScene *scene);
  std::shared_ptr<Mesh> process_mesh(aiMesh *mesh, const aiScene *scene);
  std::vector<std::shared_ptr<gl::Texture>>
  load_material_textures(aiMaterial *mat, aiTextureType type,
                         std::string type_name);
};
} // namespace flex
