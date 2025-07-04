<h1 align="center">
	🌃 &emsp; Welcome to Cub3D city &emsp; 🌆
</h1>

*A 42's project inspired by the world-famous [Wolfenstein 3D game](https://en.wikipedia.org/wiki/Wolfenstein) 🏹*


<h4 align="right">
	
  🧑🏻‍💻👩🏻‍💻 Made by [@KrisNg](https://github.com/Kr1sNg) and [@ISDouglas](https://github.com/ISDouglas)  
  
</h4>


---

## 🗺️ &ensp; Project Overview

**Cub3D** is a raycasting 3D engine built from scratch in C using the **MiniLibX** graphics library.

Inspired by the legendary *Wolfenstein 3D*, this project was developed as part of the 42 School curriculum, under strict C and system programming rules (no external dependencies, minimal libraries, low-level memory handling, etc.).

<br>

-  🛠 Built entirely in **C (C99)**  
-  🧱 Manual parsing of `.cub` configuration files  
-  🖼 Uses **MiniLibX** for rendering  
-  🎯 Real-time keyboard controls and collision detection  
-  💸 Animated sprites  


---

## 🧩 &ensp; Features

### ✅ Map Parsing

#### Parses a .cub config file:

- Texture paths (NO, SO, WE, EA)
- RGB floor and ceiling colors (F, C)
- Map layout using 1, 0, N, S, E, W
- Doors and sprites for bonus using 2, 3

#### Validates:

- Duplicate or missing entries
- Correct map closure
- Single player spawn point

### ✅ Raycasting

- Per-pixel raycasting to render a pseudo-3D environment
- Calculates wall height based on ray distance
- Texture mapping on walls
- Handle animated sprites, doors

### ✅ User Interaction

- Arrow keys or `WASD` to rotate/move
- Mouse to rotate
- Collision detection to avoid walking through walls
- Collect animated sprites
- Pass the doors open and close

### ✅ Graphics

- MiniLibX rendering
- Dynamic resolution
- Wall textures & player view
- Multiple sprites and door

---

## 👷 &ensp; How to Run

### 📦 Requirements
- macOS or Linux (X11)
- `gcc` or `clang`
- Make
- `MiniLibX` (inclued)

### 🔧 Installation

```bash
git clone https://github.com/Kr1sNg/42cursus-cub3D.git
cd cub3D
make
```

### ▶️ Run the Project

```bash
./cub3D maps/path/to/the/map.cub
```

🚀 Sample `.cub` files are available in the `/maps` directory.

🚪 Exit by pressing the `esc` key or the exit button on window.

---

## 🧪 &ensp; Sample .cub File

```cub
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

---

## 🐛 &ensp; Issues and Bugs

Please feel free to create a new issue with the title and description on the issues page of this `42cursus-cub3D` repository.

If you have already found the solution to the problem, we would love to review your `pull request`!

Thank you in advance and Happy coding!

---



