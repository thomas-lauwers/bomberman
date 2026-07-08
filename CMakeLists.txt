cmake_minimum_required(VERSION 3.28)
project(bomberman VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(logic)
add_subdirectory(representation)
add_subdirectory(tests)
