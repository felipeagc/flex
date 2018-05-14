flex_sources = [
  'window.cpp',
  'gl/vertex_buffer.cpp',
  'gl/vertex_array.cpp',
  'gl/shader.cpp',
]

flex_deps = [
  dependency('sdl2'),
  dependency('glm'),
  dependency('glad', fallback: ['glad', 'glad_dep']),
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