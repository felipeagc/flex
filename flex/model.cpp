#include "model.hpp"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <tiny_gltf.h>

using namespace flex;

Model::Model(const std::string &path) {
  tinygltf::Model model;
  tinygltf::TinyGLTF loader;
  std::string err;
  bool ret = loader.LoadBinaryFromFile(&model, &err, path);

  if (!err.empty()) {
    flex::log(L_ERROR, L_IMPORT, err);
    return;
  }

  if (!ret) {
    flex::log(L_ERROR, L_IMPORT, "Failed to parse glTF: '" + path + "'");
    return;
  }
}

Model::~Model() {}

void Model::set_texture_filter(gl::TextureFilter filter) {
  // TODO
}

void Model::draw(GraphicsSystem &graphics, glm::vec3 pos, glm::vec3 rot,
                 glm::vec3 scale) {
  // TODO
}

