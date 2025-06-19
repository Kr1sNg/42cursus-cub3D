/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:43:22 by layang            #+#    #+#             */
/*   Updated: 2025/06/19 17:14:53 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* static void	save_door_sprite(t_raycastor	*cast, t_scene *scene)
{
	if (cast->this_r < )
} */

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

static int hit_wall(char	**map, int x, int y)
{
	char c;

	c = map[y][x];
	if (c == '0' || c == 'E' || c == 'W' || c == 'N' || c == 'S')
		return (0);
	else
		return (1);
/* 	if (c == '1')
		return (1);
	else
		return (0); */
}

/* static int hit_door_sprite(char	**map, int x, int y)
{
	char c;

	c = map[y][x];

	if (c == '2' || c == '3')
		return (1);
	else
		return (0);
} */

static t_hit find_hit_side(t_raycastor	*cast, char c, int is_dir, int	is_v)
{
	if (c == '1' || is_dir == 1)
	{
		if (is_v)
		{
			if (cast->ra == M_PI / 2)
				return(NORTH);
			else if (cast->ra == 3 * M_PI / 2)
				return(SOUTH);
			else if ((cast->ra > M_PI / 2) && (cast->ra < 3 * M_PI / 2))
				return(WEST);
			else
				return(EAST);
		}
		else
		{
			if (cast->ra == 0.0)
				return(EAST);
			else if (cast->ra == M_PI)
				return(WEST);
			else if (cast->ra > M_PI)
				return(SOUTH);
			else
				return(NORTH);
		}
	}
	else if (c == '2')
		return(DOOR);
	else if (c == '3')
		return(SPRITE);
	else
		return (DEFAULT);
}

void	get_dis_v(t_raycastor	*cast, t_scene *scene, t_point p, int *depth)
{
	char	c;
	
	while (*depth < cast->dof)
	{
		cast->in_map.x = scene->tmap->player->posx + floor(cast->rx  / cast->grid) - 5;
		cast->in_map.y = scene->tmap->player->posy + floor(cast->ry  / cast->grid) - 5;
		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
				&& hit_wall(scene->tmap->the_map, cast->in_map.x, cast->in_map.y))
		{
			c = scene->tmap->the_map[cast->in_map.y][cast->in_map.x];
			cast->vx = cast->rx;
			cast->vy = cast->ry;
			cast->disV = dist(p.x, p.y, cast->vx, cast->vy);
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
	char	c;
	
	while (*depth < cast->dof)
	{
		cast->in_map.x = scene->tmap->player->posx + floor(cast->rx  / cast->grid) - 5;
		cast->in_map.y = scene->tmap->player->posy + floor(cast->ry  / cast->grid) - 5;		
		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
				&& hit_wall(scene->tmap->the_map, cast->in_map.x, cast->in_map.y))
		{
			c = scene->tmap->the_map[cast->in_map.y][cast->in_map.x];
			cast->hx = cast->rx;
			cast->hy = cast->ry;
			cast->disH = dist(p.x, p.y, cast->hx, cast->hy);
			*depth = cast->dof;
			cast->hhit = find_hit_side(cast, c, 0, 0);
			cast->hhit_dir = find_hit_side(cast, c, 1, 0);
		}
		//if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
		//&& hit_door_sprite(scene->tmap->the_map, cast->in_map.x, cast->in_map.y))
		//	save_door_sprite(cast, scene);
		else
			no_wall(scene, cast, depth);
	}	
}
