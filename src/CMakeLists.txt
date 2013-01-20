cmake_minimum_required(VERSION 2.8)

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR, "In-source build")
endif()

project(vox)

option(PROFILE "Profile the app." FALSE)
option(VALGRIND "Removes any time limmiters so Valgrind can run." FALSE)

add_definitions(${CMAKE_CXX_FLAGS_DEBUG} "-g")
add_definitions(${CMAKE_CXX_FLAGS_DEBUG} "-Wall")

if (PROFILE)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set (CMAKE_EXE_FLAGS "${CMAKE_EXE_FLAGS} -pg")
endif()

if (VALGRIND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVALGRIND")
endif()

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

find_package(OpenGL 2.0 REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT 2.8 REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

find_package(GLEW 1.9 REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

#BOOST finding
find_package(Boost 1.49 REQUIRED COMPONENTS signals)
include_directories(${Boost_INCLUDE_DIR})

find_package(SDL 1.2 REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
