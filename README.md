# Bomberman
A C++ implementation of the classic SNES Bomberman Battle Mode, featuring a clean separation of concerns between game logic and representation.

## Features
- **Bomber Movement & Bomb Placement**: Classic Bomberman controls with destructible environment mechanics.
- **Dynamic Power-ups**: Speed, blast radius, and bomb count upgrades.
- **AI Opponents**: Intelligent bombers that navigate the stage to hunt the player and other AI.
- **Scoring System**: Real-time score tracking based on gameplay events (time, power-ups, kills, broken blocks).
- **High Scores**: Persistence of top 5 scores saved to `data/highscores.txt`.

## Controls
- **Start The Game**: Enter
- **Movement**: Arrow Keys
- **Place Bomb**: Z

## Build Instructions
This project uses CMake. Ensure you have SFML and a C++17 compatible compiler installed.

```bash
cmake --build cmake-build-debug --target bomberman
```

## Running the Game
Once built, run the executable from the project root:
```bash
./cmake-build-debug/bomberman
```

## Running Tests
This project uses Google Test for unit testing.
```bash
cmake --build cmake-build-debug --target test_logic
./cmake-build-debug/test_logic
```

## Project Structure
- `include/`: Public headers for `logic`, `view`, and `utils`.
- `src/`: Source code implementation.
- `tests/`: Unit tests.
- `assets/`: Sprites, fonts, and other graphical resources.
- `data/`: Data files (e.g., high scores).

## Documentation
API documentation is generated using Doxygen.
You can view the **[online API documentation here](https://thomas-lauwers.github.io/bomberman/)**.
To generate it locally, run `doxygen Doxyfile` from the root directory. The HTML documentation will be available in the `html/` directory.

## Design Overview
The project is architected to ensure clear separation of concerns, maintainability, and extensibility.

### Architectural Patterns
- **Model-View Separation**: The game is split into `logic` (Model) and `view` (Representation). The logic layer has zero dependencies on graphics libraries (SFML), allowing for alternative renderers in the future.
- **Observer Pattern**: Used for decoupled communication between game entities (Subjects) and their graphical representations (Observers/Views).
- **Factory Pattern**: Centralizes entity creation and handles the binding of Models to their corresponding Views, reducing boilerplate code.
- **Data-Driven Assets**: Asset management is decoupled from the loading logic, making it easy to add new assets without changing code.
- **Fixed Timestep**: The game loop implements a fixed timestep to ensure deterministic game logic, regardless of the rendering framerate.
- **Singleton Pattern**: Used for global access to utility classes, specifically for `utils::Random` (random number generation) and `utils::Stopwatch` (game timing).

### Class Structure Diagram
<img width="1320" height="730" alt="diagram" src="https://github.com/user-attachments/assets/02f118ae-b849-45e7-a6a9-ce23fb82d893" />
