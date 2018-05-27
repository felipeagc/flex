#pragma once

#include "drawable.hpp"
#include "gl/texture.hpp"
#include "mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <flex/config.hpp>
#include <memory>
#include <string>
#include <vector>

namespace flex {
class Model : public Drawable {
public:
  Model(const std::string &path);
  ~Model();

  void set_texture_filter(gl::TextureFilter filter);

protected:
  void draw(GraphicsSystem &graphics, glm::vec3 pos = glm::vec3(0.0),
            glm::vec3 rot = glm::vec3(0.0),
            glm::vec3 scale = glm::vec3(1.0)) override;

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
