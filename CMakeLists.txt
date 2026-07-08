cmake_minimum_required(VERSION 3.20)
project(bomberman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(bomberman_logic
    src/Camera.cpp
    src/Score.cpp
    src/Stopwatch.cpp
    src/Random.cpp
    src/World.cpp
    src/Game.cpp
)
target_include_directories(bomberman_logic PUBLIC include)

add_executable(bomberman_app app/main.cpp)
target_link_libraries(bomberman_app PRIVATE bomberman_logic)

add_executable(bomberman_tests
    tests/test_main.cpp
    tests/test_world.cpp
)
target_link_libraries(bomberman_tests PRIVATE bomberman_logic)
add_test(NAME bomberman_tests COMMAND bomberman_tests)
