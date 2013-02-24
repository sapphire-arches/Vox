link_directories(${CMAKE_BINARY_DIR}/lib)

include_directories(.)
include_directories(../common)

add_subdirectory(engine)
add_subdirectory(ren)
add_subdirectory(state)
add_subdirectory(res)

add_executable(client main.cpp App)
target_link_libraries(client state ren common client_engine ${GLEW_LIBRARIES} ${SDL_LIBRARY} ${Boost_LIBRARIES})
