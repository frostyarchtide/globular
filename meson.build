project(
  'globular',
  'cpp',
  default_options: ['b_ndebug=if-release']
)

subdir('src')
includes = include_directories('include')

globular = library(
  'globular',
  sources,
  include_directories: includes,
  install: true
)

globular_dep = declare_dependency(
  include_directories: includes,
  link_with: globular
)

meson.override_dependency('globular', globular_dep)
