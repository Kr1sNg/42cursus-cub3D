/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:09:57 by layang            #+#    #+#             */
/*   Updated: 2025/06/25 20:14:28 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	stop_ray(t_raycastor	*cast, t_point p, int *depth)
{
	cast->rx = p.x;
	cast->ry = p.y;
	*depth = cast->dof;
}

void	intersect_v(t_raycastor	*cast, t_point p, int *depth)
{
	double	atan;

	*depth = 0;
	atan = 0.0;
	if ((cast->ra != M_PI / 2) && (cast->ra != 3 * M_PI / 2))
		atan = -tan(cast->ra);
	if ((cast->ra > M_PI / 2) && (cast->ra < 3 * M_PI / 2))
	{
		cast->rx = ((int)(p.x) / cast->grid) * cast->grid - 0.0001;
		cast->ry = (cast->rx - p.x) * atan + p.y;
		cast->stepx = -cast->grid;
		cast->stepy = cast->stepx * atan;
	}
	if ((cast->ra < M_PI / 2) || (cast->ra > 3 * M_PI / 2))
	{
		cast->rx = ((int)(p.x) / cast->grid) * cast->grid + cast->grid;
		cast->ry = (cast->rx - p.x) * atan + p.y;
		cast->stepx = cast->grid;
		cast->stepy = cast->stepx * atan;
	}
	if ((cast->ra == M_PI / 2) || (cast->ra == 3 * M_PI / 2))
		stop_ray(cast, p, depth);
}

void	get_dis_v(t_raycastor	*cast, t_scene *scene, t_point p, int *depth)
{
	char	c;

	while (*depth < cast->dof)
	{
		renew_pos_in_map(scene, cast);
		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
			&& hit_wall(scene->tmap, cast->in_map, 0) == 1)
		{
			c = scene->tmap->the_map[cast->in_map.y][cast->in_map.x];
			cast->vx = cast->rx;
			cast->vy = cast->ry;
			cast->dis_v = dist(p.x, p.y, cast->vx, cast->vy);
			*depth = cast->dof;
			cast->vhit = find_hit_side(cast, c, 0, 1);
			cast->vhit_dir = find_hit_side(cast, c, 1, 1);
		}
		else
			no_wall(scene, cast, depth);
	}
}

void	intersect_h(t_raycastor	*cast, t_point p, int *depth)
{
	double	atan;

	*depth = 0;
	atan = 0.0;
	if ((cast->ra != M_PI / 2) && (cast->ra != 3 * M_PI / 2))
		atan = -1 / tan(cast->ra);
	if (cast->ra > M_PI)
	{
		cast->ry = ((int)(p.y) / cast->grid) * cast->grid + cast->grid;
		cast->rx = (cast->ry - p.y) * atan + p.x;
		cast->stepy = cast->grid;
		cast->stepx = cast->stepy * atan;
	}
	if ((cast->ra < M_PI) && (cast->ra != 0))
	{
		cast->ry = ((int)(p.y) / cast->grid) * cast->grid - 0.0001;
		cast->rx = (cast->ry - p.y) * atan + p.x;
		cast->stepy = -cast->grid;
		cast->stepx = cast->stepy * atan;
	}
	if (cast->ra == 0 || cast->ra == M_PI)
		stop_ray(cast, p, depth);
}

void	get_dis_h(t_raycastor	*cast, t_scene *scene, t_point p, int *depth)
{
	char	c;

	while (*depth < cast->dof)
	{
		renew_pos_in_map(scene, cast);
		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
			&& hit_wall(scene->tmap, cast->in_map, 0) == 1)
		{
			c = scene->tmap->the_map[cast->in_map.y][cast->in_map.x];
			cast->hx = cast->rx;
			cast->hy = cast->ry;
			cast->dis_h = dist(p.x, p.y, cast->hx, cast->hy);
			*depth = cast->dof;
			cast->hhit = find_hit_side(cast, c, 0, 0);
			cast->hhit_dir = find_hit_side(cast, c, 1, 0);
		}
		else
			no_wall(scene, cast, depth);
	}
}
