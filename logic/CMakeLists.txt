file(GLOB_RECURSE LOGIC_SOURCES src/*.cpp)

add_library(bomberman_logic STATIC ${LOGIC_SOURCES})

target_include_directories(bomberman_logic
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# No SFML dependency for logic
