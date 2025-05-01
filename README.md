# Dapper Dasher

A side-scrolling runner game built with Raylib where you control Scarfy as he dashes through a scrolling cityscape while avoiding dangerous nebulae obstacles.


## Game Overview

In Dapper Dasher, you control a character named Scarfy who must jump over nebula obstacles. The game features:

- Smooth character animations
- Parallax scrolling background with three layers (far buildings, back buildings, and foreground)
- Physics-based jumping with gravity
- Collision detection with obstacles
- Win/lose conditions

## Controls

- **SPACE**: Jump
- **ESC**: Exit game

## Requirements

- C++ compiler with C++11 support
- Raylib graphics library
- Make (or MinGW32-make on Windows)

## Installation

### Building from Source

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/dapper-dasher.git
   cd dapper-dasher
   ```

2. Compile the game:
   ```bash
   make
   ```

3. Run the game:
   ```bash
   ./game
   ```

### Dependencies

#### Ubuntu/Debian
```bash
sudo apt install build-essential git
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
```

Then install Raylib:
```bash
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
sudo make install
```

#### Windows
Install MinGW or Visual Studio and download Raylib from the [official website](https://www.raylib.com/).

## Project Structure

```
dapper-dasher/
├── main.cpp          # Main game code
├── Makefile          # Build configuration
└── textures/         # Game assets
    ├── scarfy.png             # Player character spritesheet
    ├── 12_nebula_spritesheet.png  # Obstacle spritesheet
    ├── far-buildings.png      # Background layer 1
    ├── back-buildings.png     # Background layer 2
    └── foreground.png         # Background layer 3
```

## How It Works

### Game Mechanics

1. **Character Movement**: Scarfy automatically moves forward and can jump using the spacebar.
2. **Obstacles**: Nebula obstacles approach from the right side of the screen.
3. **Collision Detection**: If Scarfy collides with a nebula, the game ends.
4. **Win Condition**: Reach the finish line (after the last nebula).

### Technical Implementation

The game uses several key programming concepts:

- **Sprite Animation**: Both Scarfy and the nebulae are animated using spritesheets.
- **Parallax Scrolling**: Three background layers move at different speeds to create depth.
- **Physics**: Simple gravity and velocity calculations for jumping mechanics.
- **Struct-based Objects**: Game entities use the `AnimData` struct to track position, animation state, and timing.

## Customization

### Adding New Obstacles

To add more obstacles, modify the `sizeOfNebulae` constant in `main.cpp`:

```cpp
const int sizeOfNebulae{8}; // Increase this number for more obstacles
```

### Changing Game Physics

Adjust these constants in `main.cpp` to change the game feel:

```cpp
const int gravity{1000};    // Higher value = faster falling
const int jumpvel{-600};    // More negative = higher jump
int nebvel{-200};           // More negative = faster obstacles
```

## Troubleshooting

### Common Issues

- **Missing Textures**: Make sure the `textures` directory is in the same location as your executable.
- **Compilation Errors**: Ensure Raylib is properly installed and linked in the Makefile.
- **Performance Issues**: If the game runs slowly, try reducing the window size in `main.cpp`:
  ```cpp
  const int windowWidth{518};
  const int windowHeight{380};
  ```

## Contributing

Contributions are welcome! Here are some ways you can contribute:

1. Report bugs
2. Suggest features
3. Add new obstacles or game mechanics
4. Improve the code or documentation

## License

This project is released under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Built with [Raylib](https://www.raylib.com/)
- Game assets included in the project
- Inspired by endless runner games

## Future Enhancements

- Add sound effects and music
- Implement a scoring system
- Add multiple character skins
- Create more varied obstacles
- Add power-ups and special abilities
