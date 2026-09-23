*This project has been created as part of the 42 curriculum by maalonso, dcerezo-.*

# cub3D

## Description

**cub3D** is a first-person 3D game engine built from scratch in C, inspired by
the original *Wolfenstein 3D*. It renders a maze-like world described in a
simple text file, using a **ray-casting** algorithm (DDA — Digital Differential
Analysis) to project a 2D grid map into a real-time 3D view, without relying on
any external 3D or physics library.

The project's goal is to understand and implement the fundamentals of ray-casting
game engines: scene description parsing, vector/geometry math, texture mapping,
and a real-time render/input loop, all built on top of the **MiniLibX** graphics
library and a custom **libft**.

Main features:
- A custom `.cub` scene parser: wall textures (north/south/east/west), floor and
  ceiling colors, and an ASCII map, all fully validated (missing/duplicate
  fields, invalid RGB values, invalid characters, map not closed by walls, more
  than one player start, etc.).
- A ray-casting renderer with DDA wall detection, correct perpendicular
  distance (no fish-eye effect), per-wall texture mapping, and side-based
  shading.
- Smooth player movement and rotation, with wall collision so the player can
  never walk through a `1`.
- Clean shutdown and memory cleanup on window close or `ESC`.

## Instructions

### Requirements

- Linux with the X11 / Xext development headers (needed by MiniLibX).
- `gcc`/`cc`, `make`.

### Compilation

```sh
make        # builds libft, MiniLibX and the cub3D binary
make re     # rebuilds everything from scratch
make clean  # removes object files
make fclean # removes object files and the cub3D binary
```

The `Makefile` compiles with `-Wall -Wextra -Werror`, builds `libft` (in
`srcs/libft`) as a static library, and builds `minilibx-linux` from source
before linking the final `cub3D` executable.

### Running

```sh
./cub3D <path/to/map.cub>
```

The map file must end in `.cub` and contains, in any order before the map
block:

```
NO ./textures/no.xpm   # north wall texture
SO ./textures/so.xpm   # south wall texture
WE ./textures/we.xpm   # west wall texture
EA ./textures/ea.xpm   # east wall texture

F 220,100,0            # floor color, R,G,B
C 225,30,0             # ceiling color, R,G,B

1111111111
1000000001
100N000001
1000000001
1111111111
```

The map is made of `0` (floor), `1` (wall), spaces (only allowed outside the
playable area) and exactly one player start (`N`, `S`, `E` or `W`, giving the
starting orientation). It must be fully enclosed by walls, otherwise parsing
fails with an explicit error.

### Controls

| Key             | Action                    |
|-----------------|---------------------------|
| `W` / `A` / `S` / `D` | Move forward/left/back/right |
| `←` / `→`       | Rotate the camera          |
| `ESC` / close window | Quit the game         |

## Resources

Classic references used to understand and implement ray-casting:

- Lode Vandevenne — [*Raycasting*](https://lodev.org/cgtutor/raycasting.html),
  the reference tutorial for the DDA algorithm, wall distance calculation and
  texture mapping used in this engine.
- F. Permadi — [*Ray-Casting Tutorial*](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/),
  a classic explanation of the ray-casting technique used in engines like
  Wolfenstein 3D.
- [42 MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx),
  used for window/image handling and key/event hooks.
- The 42 `cub3D` subject, for the functional and Norm requirements.

### AI usage

AI assistance was used punctually to help spot a bug during
debugging (a header include-order issue that caused a compilation error).

