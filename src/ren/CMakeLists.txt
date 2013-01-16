include_directories(..)
add_library(ren 
    WorldRenderer
    TransformationManager
    RenderChunk
    RenderManager
    hud/HUD
    Mesh)
add_subdirectory(gl)
target_link_libraries(ren engine graphics state platform GL)
