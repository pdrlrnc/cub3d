*This project has been created as part of the 42 curriculum by pedde-so, vibarre.*

# cub3D

## Description

cub3D is a 3D graphical engine inspired by the iconic Wolfenstein 3D (1992), widely considered the first true first-person shooter. The project renders an interactive first-person view of a maze using raycasting, a technique that simulates 3D perspective by casting rays from the player's viewpoint and calculating wall distances to determine how tall each vertical slice of the scene should be drawn.

The program reads a scene description from a `.cub` file that specifies wall textures, floor and ceiling colors, and a tile-based map layout. It then opens a window where the player can navigate the maze in real time using keyboard controls. The engine features textured walls that vary by cardinal direction, a toggleable 2D minimap with a field-of-view cone, door mechanics with a teleportation system, and a fisheye distortion toggle.

## Instructions

### Dependencies

- A Linux environment with X11
- `cc` compiler
- `make`
- MiniLibX 

### Compilation

Clone the repository and compile:

```
make
```
If you don't have the MiniLibX library:

```
make download_mlx_linux
```

### Execution

```
./cub3D maps/subject.cub
```

Any `.cub` file can be passed as argument. Several test maps are provided in the `maps/` directory.

### Map format

The `.cub` file must contain texture paths, floor/ceiling RGB colors, and a map composed of `1` (wall), `0` (empty space), `N`/`S`/`E`/`W` (player spawn and orientation), and optionally `D` (door). The map must be enclosed by walls. Example:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

### Controls

- `W` / `S` — Move forward / backward
- `A` / `D` — Strafe left / right
- `←` / `→` — Rotate view left / right
- `E` — Teleport through a door
- `M` — Toggle minimap
- `F` — Toggle fisheye effect
- `ESC` — Quit

## Resources

### References

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — primary reference for the DDA raycasting algorithm, texture mapping, and fisheye correction
- [42 Docs - MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) — documentation for the MiniLibX graphics library
- [Wolfenstein 3D's map renderer](https://en.wikipedia.org/wiki/Wolfenstein_3D#Technology) — background on the original engine's approach
- [Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) — used for line drawing on the minimap

### AI usage

AI tools (Claude) were used as a support resource during development for the following tasks:

- **Code review**: reviewing the codebase for potential issues, Norm compliance risks, and evaluation preparedness
- **Design discussion**: reasoning through the door validation logic (neighbor configuration checks before flood fill) and the git merge workflow for integrating feature branches
- **Explaining concepts**: clarifying the perpendicular distance calculation in DDA and the fisheye correction formula

All AI-generated suggestions were reviewed, understood, and adapted by the team before integration. No code was copied verbatim from AI output without comprehension.
