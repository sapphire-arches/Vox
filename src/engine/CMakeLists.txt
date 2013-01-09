add_library(engine
    World
    WorldGenerator
    Chunk
    ChunkCache
    )
add_subdirectory(util)
target_link_libraries(engine enutil)
