CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(bomberman)
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()

FIND_PACKAGE(SFML 2.6.1 REQUIRED COMPONENTS system window graphics)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(src/logic)
add_subdirectory(src/view)

ADD_EXECUTABLE(test_logic tests/test_logic.cpp
        tests/TestEntityFactory.h)
TARGET_LINK_LIBRARIES(test_logic PRIVATE bomberman_logic GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(test_logic)