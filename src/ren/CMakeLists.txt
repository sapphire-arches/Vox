include_directories(..)
add_library(ren 
    WorldRenderer
    TransformationManager
    RenderChunk
    Mesh)
add_subdirectory(gl)
target_link_libraries(ren engine graphics state GL)
