file(GLOB_RECURSE REP_SOURCES src/*.cpp)

add_executable(bomberman ${REP_SOURCES})

target_include_directories(bomberman
    PRIVATE
        include
)

target_link_libraries(bomberman
    PRIVATE
        bomberman_logic
        sfml-graphics
        sfml-window
        sfml-system
)
