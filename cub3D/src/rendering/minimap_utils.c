/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:20:17 by layang            #+#    #+#             */
/*   Updated: 2025/06/19 12:03:09 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	inside_map_array(int x, int y, t_scene *scene)
{
	if (x < 0 || y < 0)
		return (0);
	if (y >= scene->tmap->count.map_lines)
		return (0);
	if (x >= (int)ft_strlen(scene->tmap->the_map[y]))
		return (0);
	return (1);
}

void draw_square(t_scene	*scene, t_point p, int size)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(&scene->img, (t_point){p.x + i, p.y + j, p.color});
			j++;
		}
		i++;
	}
}

void	draw_player_vector(t_scene	*scene, t_point p, int	len)
{
	double	p_angle;
	t_point vec;
	t_raycastor	*cast;

	p_angle = scene->tmap->player->p_angle;
	vec.x = (int)(p.x + cos(p_angle) * len);
	vec.y = (int)(p.y - sin(p_angle) * len);
	vec.color = p.color;
	cast = scene->tmap->player->ray2;
	line_bh(scene, p, vec, cast);
} 

double dist(double sx, double sy, double ex, double ey)
{
	return (sqrt((ex - sx) * (ex - sx) + (ey - sy) * (ey - sy)));
}

void	init_raycastor(t_point p, t_raycastor	*cast)
{
	cast->disH = 1e6;
	cast->disV = 1e6;
	cast->hx = p.x;
	cast->hy = p.y;
	cast->vx = p.x;
	cast->vy = p.y;
	cast->vhit = DEFAULT;
	cast->hhit = DEFAULT;
	cast->hit = DEFAULT;
	cast->vhit_dir = DEFAULT;
	cast->hhit_dir = DEFAULT;
	cast->hit_dir = DEFAULT;
}
