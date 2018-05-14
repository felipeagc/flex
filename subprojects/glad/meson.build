project('glad', 'c')

cc = meson.get_compiler('c')

glad_sources = [
  'src/glad.c'
]

glad_include_directories = include_directories('include')

glad_dependencies = [
  cc.find_library('dl', required: false)
]

glad = library('glad',
  glad_sources,
  include_directories: glad_include_directories,
  dependencies: glad_dependencies)

glad_dep = declare_dependency(sources: glad_sources,
  dependencies: glad_dependencies,
  link_with: glad,
  include_directories: glad_include_directories)
