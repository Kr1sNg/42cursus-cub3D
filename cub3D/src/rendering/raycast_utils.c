/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:43:22 by layang            #+#    #+#             */
/*   Updated: 2025/06/18 17:18:05 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	intersect_v(t_raycastor	*cast, t_point p, int *depth)
{
	double	atan = 0.0;
	
	*depth = 0;
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
		cast->ry = (cast->rx -p.x) * atan + p.y;
		cast->stepx = cast->grid;
		cast->stepy = cast->stepx * atan;
	}
	if ((cast->ra == M_PI / 2) || (cast->ra == 3 * M_PI / 2))
	{
		cast->rx = p.x;
		cast->ry = p.y;
		*depth = cast->dof;
	}
}

static void    no_wall(t_scene *scene, t_raycastor	*cast, int *depth)
{
    if (!inside_map_array(cast->in_map.x, cast->in_map.y, scene))
        (*depth) = cast->dof;
    else
    {
        cast->rx += cast->stepx;
        cast->ry += cast->stepy;
        (*depth)++;
    }
}

void	get_dis_v(t_raycastor	*cast, t_scene *scene, t_point p, int *depth)
{
	while (*depth < cast->dof)
	{
		cast->in_map.x = scene->tmap->player->posx + floor(cast->rx  / cast->grid) - 5;
		cast->in_map.y = scene->tmap->player->posy + floor(cast->ry  / cast->grid) - 5;
		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
				&& scene->tmap->the_map[cast->in_map.y][cast->in_map.x] == '1')
		{
			cast->vx = cast->rx;
			cast->vy = cast->ry;
			cast->disV = dist(p.x, p.y, cast->vx, cast->vy);
			*depth = cast->dof;
			if (cast->ra == M_PI / 2)
				cast->vhit = NORTH;
			else if (cast->ra == 3 * M_PI / 2)
				cast->vhit = SOUTH;
			else if ((cast->ra > M_PI / 2) && (cast->ra < 3 * M_PI / 2))
				cast->vhit = WEST;
			else
				cast->vhit = EAST;
		}
		else
            no_wall(scene, cast, depth);
	}	
}

void	intersect_h(t_raycastor	*cast, t_point p, int *depth)
{
	double	atan = 0.0;
	
	*depth = 0;
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
		cast->ry = ((int)(p.y) / cast->grid) * cast->grid  - 0.0001;
		cast->rx = (cast->ry - p.y) * atan + p.x;
		cast->stepy = -cast->grid;
		cast->stepx = cast->stepy * atan;
	}
	if (cast->ra == 0 || cast->ra == M_PI)
	{
		cast->rx = p.x;
		cast->ry = p.y;
		*depth = cast->dof;
	}
}

void	get_dis_h(t_raycastor	*cast, t_scene *scene, t_point p, int *depth)
{
	while (*depth < cast->dof)
	{
		cast->in_map.x = scene->tmap->player->posx + floor(cast->rx  / cast->grid) - 5;
		cast->in_map.y = scene->tmap->player->posy + floor(cast->ry  / cast->grid) - 5;		
		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
				&& scene->tmap->the_map[cast->in_map.y][cast->in_map.x] == '1')
		{
			cast->hx = cast->rx;
			cast->hy = cast->ry;
			cast->disH = dist(p.x, p.y, cast->hx, cast->hy);
			*depth = cast->dof;
			if (cast->ra == 0.0)
				cast->hhit = EAST;
			else if (cast->ra == M_PI)
				cast->hhit = WEST;
			else if (cast->ra > M_PI)
				cast->hhit = SOUTH;
			else
				cast->hhit = NORTH;
		}
		else
			no_wall(scene, cast, depth);
	}	
}
