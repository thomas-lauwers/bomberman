CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(bomberman)
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()

FIND_PACKAGE(SFML 2 REQUIRED COMPONENTS graphics window system)
SET(SRC main.cpp
        src/view/Game.cpp
        include/view/Game.h
        src/logic/State.cpp
        include/logic/State.h
        src/logic/PlayState.cpp
        include/logic/PlayState.h
        src/logic/TitleState.cpp
        include/logic/TitleState.h
        src/logic/PauseState.cpp
        include/logic/PauseState.h
)

ADD_EXECUTABLE(bomberman ${SRC})

TARGET_LINK_LIBRARIES(bomberman sfml-graphics sfml-window sfml-system)
INSTALL(TARGETS bomberman DESTINATION bin)