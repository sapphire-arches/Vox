include_directories(..)
add_library(engine
    World
    WorldGenerator
    Chunk
    ChunkCache
    entity/Entity
    entity/Camera
    phys/PhysicsObject
    phys/Types
    )
add_subdirectory(util)
target_link_libraries(engine enutil ren)
