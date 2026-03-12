# DoomLite

A learning project built by studying the [DOOM source code](https://github.com/id-Software/DOOM) released by id Software. The goal is to understand how a classic FPS engine works by implementing a simplified version from scratch — starting with a single level.

This is not a DOOM port or clone. It is an educational reimplementation of the core concepts: BSP rendering, sector-based maps, a software renderer, and basic game logic.

---

## Goals

- Understand the architecture of a 1990s FPS engine
- Implement a BSP-based software renderer
- Keep the code simple, readable, and well-structured
- Build incrementally, one system at a time

---

## Project Structure

```
doom-lite/
├── CMakeLists.txt
├── .clangd                      # clangd LSP configuration
└── src/
    ├── main.cpp                 # entry point and game loop
    ├── platform/
    │   ├── platform.h           # platform abstraction interface
    │   └── sdl2/
    │       └── platform_sdl2.cpp  # SDL2 implementation
    ├── wad/                     # WAD file loading (planned)
    ├── map/                     # map data and BSP tree (planned)
    ├── renderer/                # software renderer (planned)
    └── game/                    # game logic and player (planned)
```

The platform layer is intentionally abstracted behind `platform.h` so the SDL2 dependency is isolated to a single file. Adding support for other platforms later requires only a new implementation of that interface.

---

## Building

### Prerequisites

- macOS with [Homebrew](https://brew.sh)
- CMake 3.20+
- SDL2

Install dependencies:
```bash
brew install cmake sdl2
```

### Build

```bash
cmake -B build
cmake --build build
./build/DoomLite
```

Press **Escape** or close the window to quit.

---

## Credits & References

- [DOOM Source Code](https://github.com/id-Software/DOOM) — released by id Software under the GPL-2.0 license
- [Fabien Sanglard's DOOM Game Engine Black Book](https://fabiensanglard.net/gebbdoom/) — an excellent deep dive into the engine
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — helpful foundation for understanding the rendering concepts
