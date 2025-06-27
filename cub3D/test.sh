#!/bin/bash

# List of all bad map files to test
MAPS=(
    "maps/bad/color_invalid_rgb.cub"
    "maps/bad/color_missing_ceiling_rgb.cub"
    "maps/bad/color_missing.cub"
    "maps/bad/color_missing_floor_rgb.cub"
    "maps/bad/color_none.cub"
    "maps/bad/empty.cub"
    "maps/bad/file_letter_end.cub"
    "maps/bad/filetype_missing"
    "maps/bad/filetype_wrong.buc"
    "maps/bad/map_first.cub"
    "maps/bad/map_middle.cub"
    "maps/bad/map_missing.cub"
    "maps/bad/map_only.cub"
    "maps/bad/map_too_small.cub"
    "maps/bad/player_multiple.cub"
    "maps/bad/player_none.cub"
    "maps/bad/player_on_edge.cub"
    "maps/bad/test_map_hole.cub"
    "maps/bad/textures_dir.cub"
    "maps/bad/textures_duplicates.cub"
    "maps/bad/textures_invalid.cub"
    "maps/bad/textures_missing.cub"
    "maps/bad/textures_none.cub"
    "maps/bad/textures_not_xpm.cub"
    "maps/bad/wall_hole_east.cub"
    "maps/bad/wall_hole_north.cub"
    "maps/bad/wall_hole_south.cub"
    "maps/bad/wall_hole_west.cub"
    "maps/bad/wall_none.cub"
)

# Loop through each map and test with cub3D
for MAP in "${MAPS[@]}"; do
    echo "Running cub3D with map: $MAP"
    valgrind ./cub3D "$MAP"  # Replace this with your command to run cub3D
    echo "--------------------------"
done
