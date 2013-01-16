cmake_minimum_required(VERSION 2.8)

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR, "In-source build")
endif()

option(PROFILE "Profile the app." FALSE)
option(VALGRIND "Removes any time limmiters so Valgrind can run." FALSE)

project(vox)

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

find_library(OpenGL 2.0)
include_directories(${OPENGL_INCLUDE_DIR})
if (NOT ${OPENGL_FOUND})
    message(FATAL_ERROR "OpenGL not found")
endif()

find_library(GLUT 2.8)
include_directories(${GLUT_INCLUDE_DIR})
if (NOT ${GLUT_FOUND})
    message(FATAL_ERROR "GLUT not found")
endif()

find_library(GLEW 1.9)
include_directories(${GLEW_INCLUDE_DIR})
if (NOT ${GLEW_FOUND})
    message(FATAL_ERROR "GLEW not found")
endif()

find_library(Boost 1.40)
include_directories(${Boost_INCLUDE_DIR})
if (NOT ${BOOST_FOUND})
    message(FATAL_ERROR "Boost not found")
endif()

find_library(SDL 1.2)
include_directories(${SDL_INCLUDE_DIR})
if (NOT ${SDL_FOUND})
    message(FATAL_ERROR "SDL not found")
endif()

link_directories(${CMAKE_BINARY_DIR}/lib)

add_subdirectory(engine)
add_subdirectory(ren)
add_subdirectory(state)
add_subdirectory(res)
add_subdirectory(platform)

include_directories(.)

add_executable(main main.cpp App)
target_link_libraries(main state ren engine GLEW SDL)
