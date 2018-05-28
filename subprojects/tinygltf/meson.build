project('tinygltf', 'cpp')

inc_dirs = include_directories('.')

tinygltf_deps = [
  dependency('stb_image', fallback: ['stb_image', 'stb_image_dep']),
]

tinygltf_dep = declare_dependency(
  include_directories: inc_dirs,
  dependencies: tinygltf_deps,
)
