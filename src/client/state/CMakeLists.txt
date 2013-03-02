include_directories(.. .)
add_library(state
    State
    GameState
    )
target_link_libraries(state common ren client-engine)
