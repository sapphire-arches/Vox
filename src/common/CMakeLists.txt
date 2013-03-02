include_directories(.)

add_subdirectory(platform)

add_library(common-util
    engine/util/Perlin
    engine/util/Raymarch
    )
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
    )

target_link_libraries(common common-util ${BOOST_LIBRARIES})
