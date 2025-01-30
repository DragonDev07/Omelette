# src/omelette/meson.build
omelette_sources = [
  'ecs/ECS.cpp',
  'ecs/Entity.hpp',
  'ecs/Component.hpp',
  'ecs/Components/RigidBodyComponent.cpp',
  'ecs/Components/MeshComponent.cpp',
  'utils/Vec3.cpp',
  'utils/Shapes.cpp',
]

omelette_lib = static_library(
  'omelette',
  omelette_sources,
  include_directories: include_directories('.'),
  cpp_args: ['-g'] # Add debugging symbols,,,,
)

omelette_dep = declare_dependency(
  include_directories: include_directories('.'),
  link_with: omelette_lib,
  dependencies: [glm_dep],
)
