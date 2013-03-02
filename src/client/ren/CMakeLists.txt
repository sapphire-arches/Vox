include_directories(..)
add_library(ren
    WorldRenderer
    TransformationManager
    RenderChunk
    RenderManager
    EntityRenderer
    hud/HUD
    Mesh)
add_subdirectory(gl)
target_link_libraries(ren common graphics state platform ${OPENGL_gl_LIBRARY} ${BOOST_LIBRARIES})
