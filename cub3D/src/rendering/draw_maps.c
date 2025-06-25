/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:20:17 by layang            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/25 12:35:40 by tat-nguy         ###   ########.fr       */
=======
/*   Updated: 2025/06/25 12:33:55 by layang           ###   ########.fr       */
>>>>>>> 6ab087a (try to get close to the sprite)
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_square_minimap(t_scene	*scene, t_point p, int size,
	t_point c[4])
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (p.x + i >= c[0].x && p.y + j >= c[0].y
				&& p.x + i <= c[3].x && p.y + j <= c[3].y)
				put_pixel(&scene->img, (t_point){p.x + i, p.y + j, p.color});
			j++;
		}
		i++;
	}
}

static void	draw_minimap_tile(t_scene *s, t_point lp, t_point p, t_point *cor)
{
	t_point	map_p;
	t_point	pix_p;
	char	c;
	int		grid;

	grid = s->tmap->player->ray2->grid;
	map_p.x = s->tmap->player->posx + lp.x;
	map_p.y = s->tmap->player->posy + lp.y;
	if (inside_map_array(map_p.x, map_p.y, s))
	{
		c = s->tmap->the_map[map_p.y][map_p.x];
		if (c && (c == '1' || c == '0' || c == 'N' || c == 'S'
				|| c == 'W' || c == 'E' || c == '2' || c == '3'))
		{
			pix_p.color = 0xFFD580;
			if (c == '1')
				pix_p.color = 0x666666;
			if (c == '2')
				pix_p.color = 0xFFD000;
			pix_p.x = p.x + lp.x * grid + 1;
			pix_p.y = p.y + lp.y * grid + 1;
			draw_square_minimap(s, pix_p, grid - 1, cor);
		}
	}
}

static void	draw_minimap(t_scene	*scene, t_point	p)
{
	int		x;
	int		y;
	t_point	cor[4];

	cor[0].x = (int)(WIDTH / 50);
	cor[0].y = (int)(HEIGHT / 50);
	cor[1].x = cor[0].x + round((WIDTH + HEIGHT) / 10);
	cor[1].y = cor[0].y;
	cor[2].x = cor[0].x;
	cor[2].y = cor[0].y + round((WIDTH + HEIGHT) / 10);
	cor[3].x = cor[0].x + round((WIDTH + HEIGHT) / 10);
	cor[3].y = cor[0].y + round((WIDTH + HEIGHT) / 10);
	y = -5;
	while (y < 5)
	{
		x = -5;
		while (x < 5)
		{
			draw_minimap_tile(scene, (t_point){x, y, 0}, p, cor);
			x++;
		}
		y++;		
	}	
}

void	draw_maps(t_scene	*scene)
{
	int		size = round((WIDTH + HEIGHT) / scene->tmap->visible);
	t_point	center;
	int		grid;
	t_point	start;
	t_point	draw_start;
	int		size_player;
	
	scene->tmap->player->ray2->grid = size / scene->tmap->visible;
	grid = scene->tmap->player->ray2->grid;
	start.x = (int)(WIDTH / (5 * scene->tmap->visible));
	start.y = (int)(HEIGHT / (5 * scene->tmap->visible));
	start.color = gradient_color(0.3, WHITE, scene->tmap->color_c);
	draw_start.x = start.x + (scene->tmap->visible / 2) * grid;
	draw_start.y = start.y + (scene->tmap->visible / 2) * grid;
	size_player = grid / 3;
	center.x = draw_start.x + grid / 2 + scene->tmap->player->ray2->offx;
	center.y = draw_start.y + grid / 2 + scene->tmap->player->ray2->offy;
	center.color = 0x000000;
	draw_3d_scene(scene, center, grid, start);
	draw_square(scene, start, size);
	draw_minimap(scene, draw_start);
	draw_player_vision(scene, center, grid, start);
	draw_player_vector(scene, center, grid / 2);
	draw_square(scene, (t_point){center.x - size_player / 2,
		center.y - size_player / 2, 0xDE3163}, size_player);
}
