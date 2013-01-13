include_directories(..)
add_library(engine
    World
    WorldGenerator
    Chunk
    ChunkCache
    entity/Entity
    phys/PhysicsObject
    phys/Types
    )
add_subdirectory(util)
target_link_libraries(engine enutil ren)
