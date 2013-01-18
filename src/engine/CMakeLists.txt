include_directories(..)
add_library(engine
    World
    WorldGenerator
    Chunk
    ChunkCache
    entity/Entity
    entity/PlayerEntity
    entity/Camera
    entity/Rocket
    phys/PhysicsObject
    phys/Types
    util/Perlin
    util/Raymarch
    )
target_link_libraries(engine ren)
