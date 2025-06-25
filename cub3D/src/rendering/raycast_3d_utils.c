/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3d_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:02:25 by layang            #+#    #+#             */
/*   Updated: 2025/06/25 14:52:42 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_render_height(t_raycastor	*cast, t_scene *scene, t_ray_hit	hit)
{			
	double	ca;
	double	no_fisheye_dist;
	double	proj_plane_dist;
	
	ca = normalize_angle(scene->tmap->player->p_angle - cast->ra);
	no_fisheye_dist = hit.dist * cos(ca);
	proj_plane_dist = (WIDTH / 2.0) / tan(scene->tmap->player->fov / 2.0);
	cast->rend_h = (int)((cast->grid / no_fisheye_dist) * proj_plane_dist);
	cast->ori_rend_h = cast->rend_h;
	if (cast->rend_h > HEIGHT)
		cast->rend_h = HEIGHT;
	cast->ori_off = (HEIGHT - cast->rend_h) / 2;
	cast->draw_off = cast->ori_off;
}

int have_repeat(t_point in,  t_ray	*hitps, double	dist)
{
	int	n;
	int	i;
	t_point	hit;

	i = 0;
	n = hitps->hit_count;
	while (i < n)
	{
		hit = hitps->hits[i].hit_map;
		if (hit.x == in.x && hit.y == in.y)
		{
			if (dist < hitps->hits[i].dist)
				return (i);
			else
				return (-1);
		}
		i++;
	}
	return (-2);
}

t_pic	find_texture_3d(t_scene	*scene, t_ray_hit	hit)
{		
	if (hit.hit_type == DEFAULT)
		return ((t_pic){NULL, NULL, 0, 0, 0, 0, 0});
	else if (hit.hit_type == NORTH)
		return (scene->tmap->tex_n);
	else if (hit.hit_type == SOUTH)
		return (scene->tmap->tex_s);
	else if (hit.hit_type == EAST && scene->tmap->sprite_on)
		return (scene->tmap->tex_e);
	else if (hit.hit_type == WEST)
		return (scene->tmap->tex_w);
	else if (hit.hit_type == DOOR)
		return (scene->tmap->door);
	else
		return (scene->tmap->sprite);
}
