link_directories(${CMAKE_BINARY_DIR}/lib)

add_subdirectory(engine)
add_subdirectory(ren)
add_subdirectory(state)
add_subdirectory(res)
add_subdirectory(platform)

include_directories(.)

add_executable(client main.cpp App)
target_link_libraries(client state ren engine ${GLEW_LIBRARIES} ${SDL_LIBRARY})
