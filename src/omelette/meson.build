# src/omlette/meson.build
omelette_sources = [
  'Vec3.cpp',
  'PhysicsWorld.cpp',
  'RigidBody.cpp',
]

omelette_lib = static_library(
  'omelette',
  omelette_sources,
  include_directories: include_directories('.'),
  cpp_args: ['-g']  # Add debugging symbols
)