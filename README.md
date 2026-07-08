# bomberman

This repository now contains a C++ Bomberman project scaffold focused on the required architecture:

- **Logic library** (`bomberman_logic`) separate from representation code.
- Required key classes: `Game`, `World`, `Camera`, `Score`, `Stopwatch` (Singleton), `Random` (Singleton).
- Required patterns applied in the codebase:
  - MVC separation (logic in `include/bomberman` + `src`, representation entrypoint in `app/main.cpp`)
  - Observer (`IObserver`, `Subject`, `Score` subscriptions)
  - Abstract Factory (`AbstractFactory` interface)
  - Singleton (`Stopwatch`, `Random`)
- Core gameplay logic implemented in `World`:
  - Arena generation with indestructible/destructible tiles
  - Player + 3 bot spawns in corners
  - Continuous movement with collision checks
  - Bomb placement, timed explosions, chain reactions
  - Destructible block destruction and random power-up drops
  - Fire / Extra Bomb / Skates power-up effects
  - Basic bot behavior (danger avoidance, power-up pursuit, wall breaking, enemy pressure)
- Scoring events and persisted top-5 highscores via `Score`.
- Focused logic tests included under `tests/`.

## Build

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```
