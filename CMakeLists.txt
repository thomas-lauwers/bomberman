CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(bomberman)
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()

FIND_PACKAGE(SFML REQUIRED COMPONENTS system window graphics)

SET(LOGIC_SRC 
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
        src/logic/Camera.cpp
        include/logic/Camera.h
        src/utils/Random.cpp
        include/utils/Random.h
        src/logic/Tile.cpp
        include/logic/Tile.h
        include/logic/Observer.h
        include/logic/Subject.h
        src/utils/Stopwatch.cpp
        include/utils/Stopwatch.h
        include/logic/factory/IEntityFactory.h
        src/logic/factory/Player.cpp
        include/logic/factory/Player.h
        src/logic/Rect.cpp
        include/logic/Rect.h
        include/logic/factory/Entity.h
        src/logic/factory/Bomb.cpp
        include/logic/factory/Bomb.h
        src/logic/factory/DestructibleWall.cpp
        include/logic/factory/DestructibleWall.h
        include/utils/Position.h
)

SET(VIEW_SRC 
        main.cpp
        src/view/Game.cpp
        include/view/Game.h
        src/view/WorldRenderer.cpp
        include/view/WorldRenderer.h
        src/view/TextureManager.cpp
        include/view/TextureManager.h
        include/view/IEntityView.h
        src/view/PlayerView.cpp
        include/view/PlayerView.h
        src/view/DestructibleWallView.cpp
        include/view/DestructibleWallView.h
        src/view/BombView.cpp
        include/view/BombView.h
        src/view/ViewportUtility.cpp
        include/view/ViewportUtility.h
        src/view/factory/BattleStageFactory.cpp
        include/view/factory/BattleStageFactory.h
        src/logic/factory/Explosion.cpp
        src/view/ExplosionView.cpp
        include/view/ExplosionView.h
        src/view/ExplosionView.cpp
        include/view/Direction.h
        include/view/AnimationState.h
        include/view/BomberAnimationConfig.h
        src/view/BomberAnimationConfig.cpp
        include/view/BomberAnimationConfig.h
        include/view/Animation.h
)

ADD_LIBRARY(bomberman_logic STATIC ${LOGIC_SRC})

ADD_EXECUTABLE(bomberman ${VIEW_SRC})

TARGET_LINK_LIBRARIES(bomberman bomberman_logic sfml-graphics sfml-window sfml-system)
INSTALL(TARGETS bomberman DESTINATION bin)