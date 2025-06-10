/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:20:17 by layang            #+#    #+#             */
/*   Updated: 2025/06/10 16:04:57 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_3d.h"

static void	draw_minimap(t_scene	*scene, int grid, t_point	player)
{
	//int		visi_half = size / (2 * grid);
	int		x;
	int		y;
	char	c;
	t_point	pix_p;
	t_point	map_p;
	int		col;
	int		off;

	//printf("visi_half : %d\n", visi_half);
	y = -5;
	while (y < 5)
	{
		x = -5;
		while (x < 5)
		{
			map_p.x = scene->tmap->player.posx + x;
			map_p.y = scene->tmap->player.posy + y;
			//printf("map: (%d,%d)\n", map_p.x, map_p.y);
			if (inside_map_array(map_p.x, map_p.y, scene))
			{
				c = scene->tmap->map[map_p.y][map_p.x];
				if (c && (c == '1' || c == '0' || c == 'N' || c == 'S'
						|| c == 'W' || c == 'E'))
				{
					if (c == '1')
						col = 0x666666;
					else
						col = 0xFFD580;
					if (c == '1')
						off = 1;
					else
						off = 0;
					pix_p.x = player.x + x * grid + off;
					pix_p.y = player.y + y * grid + off;
					pix_p.color = col;
					//printf("Draw square at pixel (%d,%d)\n", pix_p.x, pix_p.y);
					draw_square(scene, pix_p, grid - off);
				}
			}
			x++;
		}
		y++;		
	}		
}

void	put_minimap(t_scene	*scene)
{
	int		size = round((WIDTH + HEIGHT)/ 10);
	t_point	center;
	int		grid = size / 10;
	t_point	start;
	t_point	draw_start;
	int		size_player;
	
	start.x = (int)(WIDTH / 50);
	start.y = (int)(HEIGHT / 50);
	start.color = 0x00FFFFFF;
	draw_start.x = start.x + 5 * grid;
	draw_start.y = start.y + 5 * grid;
	draw_square(scene, start, size);
	draw_minimap(scene, grid, draw_start);
	size_player = grid / 3;
	center.x = draw_start.x + grid / 2;
	center.y = draw_start.y + grid / 2;
	center.color = 0x000000;
	//draw_player_vision(scene, center, grid);
	draw_player_vector(scene, center, grid / 2);
	draw_square(scene, (t_point){center.x - size_player / 2,
		center.y - size_player / 2, 0xDE3163}, size_player);
}
