add_library(ren 
    WorldRenderer
    RenderChunk
    Mesh)
add_subdirectory(gl)
target_link_libraries(ren engine graphics GL)
