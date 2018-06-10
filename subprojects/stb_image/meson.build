project('stb_image', 'cpp')

inc_dirs = include_directories('.')

sources = [
  'stb_image.cpp',
]

stb_image_lib = library(
  'stb_image',
  sources: sources,
  include_directories: inc_dirs,
)

stb_image_dep = declare_dependency(
  link_with: stb_image_lib,
  include_directories: inc_dirs,
)
