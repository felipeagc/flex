flex_sources = [
  'window.cpp',
  'mesh.cpp',
  'model.cpp',
  'camera.cpp',
  'gl/buffer.cpp',
  'gl/vertex_buffer.cpp',
  'gl/index_buffer.cpp',
  'gl/vertex_array.cpp',
  'gl/texture.cpp',
  'gl/framebuffer.cpp',
  'gl/renderbuffer.cpp',
  'gl/shader.cpp',
]

flex_deps = [
  dependency('sdl2'),
  dependency('glm'),
  dependency('assimp'),
  dependency('glad', fallback: ['glad', 'glad_dep']),
  dependency('stb_image', fallback: ['stb_image', 'stb_image_dep']),
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
