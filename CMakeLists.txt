CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(bomberman)
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()

FIND_PACKAGE(SFML REQUIRED COMPONENTS system window graphics)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

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
        src/logic/factory/Explosion.cpp
        src/logic/factory/CrumblingWall.cpp
        include/logic/factory/CrumblingWall.h
        include/utils/Position.h
        src/logic/factory/PowerUp.cpp
        include/logic/factory/PowerUp.h
        src/logic/factory/KnockedOutBomber.cpp
        include/logic/factory/KnockedOutBomber.h
)

SET(VIEW_SRC 
        main.cpp
        src/view/core/Game.cpp
        include/view/core/Game.h
        src/view/core/WorldRenderer.cpp
        include/view/core/WorldRenderer.h
        src/view/core/TextureManager.cpp
        include/view/core/TextureManager.h
        include/view/entities/IEntityView.h
        src/view/entities/PlayerView.cpp
        include/view/entities/PlayerView.h
        src/view/entities/DestructibleWallView.cpp
        include/view/entities/DestructibleWallView.h
        src/view/entities/BombView.cpp
        include/view/entities/BombView.h
        src/view/ViewportUtility.cpp
        include/view/ViewportUtility.h
        src/view/factory/BattleStageFactory.cpp
        include/view/factory/BattleStageFactory.h
        src/view/entities/ExplosionView.cpp
        include/view/entities/ExplosionView.h
        src/view/entities/ExplosionView.cpp
        include/view/Direction.h
        include/view/AnimationState.h
        include/view/BomberAnimationConfig.h
        src/view/BomberAnimationConfig.cpp
        include/view/BomberAnimationConfig.h
        include/view/Animation.h
        src/view/entities/CrumblingWallView.cpp
        include/view/entities/CrumblingWallView.h
        src/view/entities/PowerUpView.cpp
        include/view/entities/PowerUpView.h
        src/view/entities/KnockedOutBomberView.cpp
        include/view/entities/KnockedOutBomberView.h
)

ADD_LIBRARY(bomberman_logic STATIC ${LOGIC_SRC})

ADD_EXECUTABLE(bomberman ${VIEW_SRC})

TARGET_LINK_LIBRARIES(bomberman bomberman_logic sfml-graphics sfml-window sfml-system)
INSTALL(TARGETS bomberman DESTINATION bin)

ADD_EXECUTABLE(test_logic tests/test_logic.cpp
        tests/TestEntityFactory.h)
TARGET_LINK_LIBRARIES(test_logic PRIVATE bomberman_logic GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(test_logic)