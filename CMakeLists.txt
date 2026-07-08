CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(bomberman)
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()

FIND_PACKAGE(SFML REQUIRED COMPONENTS System Window Graphics)
SET(SRC main.cpp
        src/view/Game.cpp
        include/view/Game.h
        src/logic/State.cpp
        src/logic/State.h
        src/logic/PlayState.cpp
        src/logic/PlayState.h
        src/logic/TitleState.cpp
        src/logic/TitleState.h
        src/logic/PauseState.cpp
        src/logic/PauseState.h
)

ADD_EXECUTABLE(bomberman ${SRC})

TARGET_LINK_LIBRARIES(bomberman SFML::Graphics SFML::Window SFML::System)
INSTALL(TARGETS bomberman DESTINATION bin)