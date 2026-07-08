CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(bomberman)
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()

FIND_PACKAGE(SFML 3.1.0 COMPONENTS System Window Graphics)

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

INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

ADD_EXECUTABLE(bomberman ${SRC})

TARGET_LINK_LIBRARIES(bomberman sfml-system sfml-graphics sfml-window)

INSTALL(TARGETS bomberman DESTINATION bin)