include_directories(..)
add_library(engine
    World
    WorldGenerator
    Chunk
    ChunkCache
    entity/Entity
    )
add_subdirectory(util)
target_link_libraries(engine enutil ren)
