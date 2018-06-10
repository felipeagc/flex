flex_sources = [
  'engine.cpp',
  'window.cpp',
  'audio.cpp',
  'graphics.cpp',
  'app.cpp',

  'sprite.cpp',
  'mesh.cpp',
  'instancedmesh.cpp',
  'gltfmodel.cpp',
  'instancedgltfmodel.cpp',
  'camera.cpp',
  'canvas.cpp',

  'gl/buffer.cpp',
  'gl/vertex_array.cpp',
  'gl/texture.cpp',
  'gl/framebuffer.cpp',
  'gl/renderbuffer.cpp',
  'gl/shader.cpp',
]

add_project_arguments('-DGLM_ENABLE_EXPERIMENTAL', language: 'cpp')

flex_deps = [
  dependency('gl'),
  dependency('sdl2'),
  dependency('glm'),
  dependency('assimp'),
  dependency('epoxy'),
  dependency('stb_image', fallback: ['stb_image', 'stb_image_dep']),
  dependency('soloud', fallback: ['soloud', 'soloud_dep']),
  dependency('imgui', fallback: ['imgui', 'imgui_dep']),
  dependency('tinygltf', fallback: ['tinygltf', 'tinygltf_dep']),
]

conf_data = configuration_data()
conf_data.set('res_path', '../resources')
configure_file(
  input: 'config.hpp.in',
  output: 'config.hpp',
  configuration: conf_data,
)

flex_inc = include_directories('..')

flex = library(
  'flex',
  flex_sources,
  dependencies: flex_deps,
  include_directories: flex_inc,
)

flex_dep = declare_dependency(
  link_with: flex,
  include_directories: flex_inc,
  dependencies: flex_deps,
)
