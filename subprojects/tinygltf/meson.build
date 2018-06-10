project('tinygltf', 'cpp')

inc_dirs = include_directories('.')

tinygltf_deps = [
  dependency('stb_image', fallback: ['stb_image', 'stb_image_dep']),
]

sources = [
  'tiny_gltf.cpp'
]

tinygltf_lib = library(
  'tinygltf',
  sources: sources,
  include_directories: inc_dirs,
  dependencies: tinygltf_deps,
)

tinygltf_dep = declare_dependency(
  link_with: tinygltf_lib,
  include_directories: inc_dirs,
  dependencies: tinygltf_deps,
)
