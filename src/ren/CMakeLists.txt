add_library(ren 
    WorldRenderer
    Mesh)
add_subdirectory(gl)
target_link_libraries(ren engine graphics GL)
