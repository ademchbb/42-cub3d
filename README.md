*This project has been created as part of the 42 curriculum by ragolden and adchebbi.*

# cub3D

## Description

**cub3D** is a first-person raycasting engine written in C, inspired by the
original *Wolfenstein 3D*. Its goal is to build a simplified 3D graphical
representation of a maze from a scene description file (`.cub`), using
ray-casting principles and the MinilibX graphics library.

The project covers the full pipeline of a small game engine:

- Parsing and strict validation of a custom `.cub` scene file (textures,
  floor/ceiling colors, and a map made of walls, empty spaces, and a
  player spawn point with orientation).
- A raycasting engine based on the Digital Differential Analysis (DDA)
  algorithm, producing a real-time first-person view of the map.
- Wall textures that differ depending on which side is being looked at
  (north, south, east, west), computed and mapped per screen column.
- Textured floor and ceiling rendering (floor/ceiling casting), including
  a procedurally generated starry "glass ceiling" texture.
- Smooth player movement (`W`/`A`/`S`/`D`) and camera rotation (arrow
  keys), with collision detection against the map's walls.
- Clean window management: the program exits properly on `ESC` or when
  the window's close button is clicked, and the window keeps responding
  while switching focus, minimizing, etc.

## Instructions

### Compilation

```sh
make        # builds the cub3D executable
make clean  # removes object files
make fclean # removes object files and the executable
make re     # rebuilds everything from scratch
```

The Makefile compiles the project's own sources, the bundled `libft`, and
the bundled MinilibX library, then links everything together.

### Running

```sh
./cub3D maps/<your_map>.cub
```

The program takes exactly one argument: a scene description file with the
`.cub` extension.

### Controls

| Key            | Action                          |
|----------------|----------------------------------|
| `W` / `A` / `S` / `D` | Move forward / left / back / right |
| `←` / `→`      | Turn the camera left / right    |
| `ESC`          | Quit the program                |
| Close button   | Quit the program                |

### Map file format

A `.cub` file combines a configuration section (in any order) and a map
(always last):

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

- `NO`/`SO`/`WE`/`EA`: paths to the wall textures for each direction.
- `F`/`C`: floor and ceiling colors, as `R,G,B` values in `[0, 255]`.
- The map itself uses `0` (empty space), `1` (wall), and one of
  `N`/`S`/`E`/`W` for the player's starting position and orientation.
  The map must be fully enclosed by walls.

## Resources

- [Ray-Casting tutorial — lodev.org](https://lodev.org/cgtutor/raycasting.html) —
  the main reference used for the DDA algorithm, the direction
  vector/camera plane model, and the perpendicular wall distance
  (fisheye correction) formula, later extended for wall, floor and
  ceiling texture mapping.
- [Ray-casting information](https://hackmd.io/@nszl/H1LXByIE2) - Very usefoool to anderstand the DDA algo, 
  anti fish-eye solution and good grafical illustrations !
- The official 42 cub3D subject.
- MinilibX man pages (`mlx_init`, `mlx_new_window`, `mlx_hook`,
  `mlx_xpm_file_to_image`, `mlx_get_data_addr`, ...).
- *Wolfenstein 3D* (id Software, 1992) as the historical reference for
  the genre.

### AI usage

Claude (Anthropic) was used throughout this project as a learning and
pair-programming assistant, in the following way:

- **Explaining concepts and math**: breaking down the DDA algorithm, the
  direction/camera plane model, and the perpendicular wall distance
  formula into applicable steps, without writing the implementation.
