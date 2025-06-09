/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:20:17 by layang            #+#    #+#             */
/*   Updated: 2025/06/07 14:27:55 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_3d.h"

void draw_square(t_scene	*scene, t_point p, int size, unsigned int color)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(&scene->img, (t_point){p.x + i, p.y + j, color});
			j++;
		}
		i++;
	}
}

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
			if (map_p.x >= 0 && map_p.y >= 0 && map_p.x < scene->tmap->map_w
					&& map_p.y < scene->tmap->map_h
					&& map_p.x < (int)ft_strlen(scene->tmap->map[map_p.y]))
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
					//printf("Draw square at pixel (%d,%d)\n", pix_p.x, pix_p.y);
					draw_square(scene, pix_p, grid - off, col);
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
	int		grid;
	t_point	start;
	
	center.x = (int)(WIDTH / 50 + size / 2);
	center.y = (int)(HEIGHT / 50 + size / 2);
	start.x = (int)(WIDTH / 50);
	start.y = (int)(HEIGHT / 50);
	grid = size / 10;
	draw_square(scene, start, size, 0x00FFFFFF);
	draw_minimap(scene, grid, center);
	center.x += size / 40;
	center.y += size / 40;
	draw_square(scene, center, grid / 2, 0xDE3163);
}
