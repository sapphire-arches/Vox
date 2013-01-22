add_library(client-engine
    NetworkChunkProvider
    NetworkListner
    )
message (STATUS "Fix the hardcoded include in client/engine/CMakeLists.txt:")
message (STATUS "BOOST_LIBRARIES: ${BOOST_LIBRARIES}")
if (UNIX AND NOT APPLE)
    message (STATUS "Working around linux weirdness in client/engine/CMakeLists.txt:8")
    target_link_libraries(client-engine rt)
endif()
target_link_libraries(client-engine boost_system boost_thread)
