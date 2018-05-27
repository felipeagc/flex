project('imgui', 'cpp')

imgui_inc = include_directories('.')

imgui_sources = [
  'imgui.cpp',
  'imgui_draw.cpp',
  'imgui_demo.cpp',
  'imgui_impl_sdl_gl3.cpp',
]

imgui_deps = [
  dependency('epoxy'),
  dependency('sdl2'),
]

imgui = library(
  'imgui',
  sources: imgui_sources,
  include_directories: imgui_inc,
  dependencies: imgui_deps,
)

imgui_dep = declare_dependency(
  link_with: imgui,
  include_directories: imgui_inc
)
