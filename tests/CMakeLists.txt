add_executable(test_world test_world.cpp)

target_link_libraries(test_world
    PRIVATE
        bomberman_logic
)
