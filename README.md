# Bomberman
A C++ implementation of the classic Bomberman game, featuring a clean separation of concerns between game logic and representation.

## Features
- **Modular Architecture**: Clear separation between `logic` (Model) and `view` (Representation) layers.
- **Observer Pattern**: Decoupled communication using Subject-Observer architecture.
- **Event-Driven Scoring**: Real-time score tracking based on gameplay events (time, power-ups, kills, broken blocks).
- **Data-Driven Assets**: Robust asset management with error handling.
- **Persistence**: High score tracking saved to `data/highscores.txt`.

## Build Instructions
This project uses CMake. Ensure you have SFML and a C++17 compatible compiler installed.

```bash
# Build the project
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
API documentation is generated using Doxygen. To generate it, run `doxygen Doxyfile` from the root directory. The HTML documentation will be available in the `html/` directory.