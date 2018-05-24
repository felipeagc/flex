#include "model.hpp"

using namespace flex;

Model::Model(std::string path) {
  Assimp::Importer import;
  const aiScene *scene =
      import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    flex::log(L_ERROR, L_IMPORT,
              std::string("Assimp error: ") + import.GetErrorString());
    return;
  }

  m_directory = path.substr(0, path.find_last_of('/'));

  process_node(scene->mRootNode, scene);

  flex::log(L_DEBUG, L_IMPORT, "Model loaded: " + path);
}

Model::~Model() {}

void Model::draw(gl::Shader &shader) {
  for (auto &mesh : m_meshes) {
    mesh->draw(shader);
  }
}

void Model::process_node(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    m_meshes.push_back(process_mesh(mesh, scene));
  }

  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    process_node(node->mChildren[i], scene);
  }
}

std::shared_ptr<Mesh> Model::process_mesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<std::shared_ptr<gl::Texture>> diffuse_textures;
  std::vector<std::shared_ptr<gl::Texture>> specular_textures;
  std::vector<std::shared_ptr<gl::Texture>> normal_textures;
  std::vector<std::shared_ptr<gl::Texture>> height_textures;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;

    vertex.pos.x = mesh->mVertices[i].x;
    vertex.pos.y = mesh->mVertices[i].y;
    vertex.pos.z = mesh->mVertices[i].z;

    vertex.color = {1.0, 1.0, 1.0};

    vertex.normal.x = mesh->mNormals[i].x;
    vertex.normal.y = mesh->mNormals[i].y;
    vertex.normal.z = mesh->mNormals[i].z;

    if (mesh->mTextureCoords[0]) {
      vertex.tex_coords.x = mesh->mTextureCoords[0][i].x;
      vertex.tex_coords.y = mesh->mTextureCoords[0][i].y;
    } else {
      vertex.tex_coords = {0.0, 0.0};
    }

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  if (mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    diffuse_textures = load_material_textures(material, aiTextureType_DIFFUSE,
                                              "texture_diffuse");
    specular_textures = load_material_textures(material, aiTextureType_SPECULAR,
                                               "texture_specular");
    normal_textures = load_material_textures(material, aiTextureType_NORMALS,
                                             "texture_normal");
    height_textures = load_material_textures(material, aiTextureType_HEIGHT,
                                             "texture_height");
  }

  return std::shared_ptr<Mesh>(new Mesh(vertices, indices, diffuse_textures,
                                        specular_textures, normal_textures,
                                        height_textures));
}

std::vector<std::shared_ptr<gl::Texture>>
Model::load_material_textures(aiMaterial *mat, aiTextureType type,
                              std::string type_name) {
  std::vector<std::shared_ptr<gl::Texture>> textures;

  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);

    bool skip = false;
    for (unsigned int j = 0; j < m_textures_loaded.size(); j++) {
      auto path = m_textures_loaded[j]->get_path();
      auto filename = path.substr(path.find_last_of('/') + 1, path.length());

      if (std::strcmp(filename.data(), str.C_Str()) == 0) {
        textures.push_back(m_textures_loaded[j]);
        skip = true;
        break;
      }
    }

    if (!skip) {
      std::shared_ptr<gl::Texture> texture = std::make_shared<gl::Texture>();
      std::string path = this->m_directory + '/' + std::string(str.C_Str());
      texture->load_from_file(path);

      textures.push_back(texture);
      m_textures_loaded.push_back(texture);
    }
  }

  return textures;
}
