include_directories(.)

add_subdirectory(platform)

add_library(common
    engine/World
    engine/WorldGenerator
    engine/Chunk
    engine/ChunkCache
    engine/entity/Entity
    engine/entity/PlayerEntity
    engine/entity/Camera
    engine/entity/Rocket
    engine/phys/PhysicsObject
    engine/phys/Types
    engine/util/Perlin
    engine/util/Raymarch
    )

target_link_libraries(common ${BOOST_LIBRARIES})
