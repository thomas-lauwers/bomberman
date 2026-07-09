CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(bomberman)
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()

FIND_PACKAGE(SFML REQUIRED COMPONENTS system window graphics)
SET(SRC main.cpp
        src/view/Game.cpp
        include/view/Game.h
        src/logic/state/State.cpp
        include/logic/state/State.h
        src/logic/state/PlayState.cpp
        include/logic/state/PlayState.h
        src/logic/state/TitleState.cpp
        include/logic/state/TitleState.h
        src/logic/state/PauseState.cpp
        include/logic/state/PauseState.h
        src/logic/state/StateManager.cpp
        include/logic/state/StateManager.h
        src/logic/World.cpp
        include/logic/World.h
        src/view/WorldRenderer.cpp
        include/view/WorldRenderer.h
        src/util/ViewportUtility.cpp
        include/util/ViewportUtility.h
        src/logic/Camera.cpp
        include/logic/Camera.h
        src/logic/Random.cpp
        include/logic/Random.h
)

ADD_EXECUTABLE(bomberman ${SRC})

TARGET_LINK_LIBRARIES(bomberman sfml-graphics sfml-window sfml-system)
INSTALL(TARGETS bomberman DESTINATION bin)