project(
  'globular',
  'cpp',
  default_options: ['b_ndebug=if-release']
)

epoxy_dep = dependency('epoxy')
glfw3_dep = dependency('glfw3')
imgui_dep = dependency('imgui')
x11_dep = dependency('x11')
gl_dep = dependency('GL')

subdir('src')
includes = include_directories('include')

globular = library(
  'globular',
  sources,
  dependencies: [epoxy_dep, glfw3_dep, imgui_dep, x11_dep, gl_dep],
  include_directories: includes,
  install: true
)

globular_dep = declare_dependency(
  include_directories: includes,
  link_with: globular
)

meson.override_dependency('globular', globular_dep)
