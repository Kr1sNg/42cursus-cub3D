/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3d_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin < layang@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:55:59 by marvin            #+#    #+#             */
/*   Updated: 2025/06/21 17:55:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_pic	find_texture_3d(t_scene	*scene, t_ray_hit	hit)
{	
	//int	x;
	
	if (hit.hit_type == DEFAULT)
		return ((t_pic){NULL, NULL, 0, 0, 0, 0, 0});
	else if (hit.hit_type == NORTH)
		return (scene->tmap->tex_n);
	else if (hit.hit_type == SOUTH)
		return (scene->tmap->tex_s);
	else if (hit.hit_type == EAST)
		return (scene->tmap->tex_e);
	else if (hit.hit_type == WEST)
		return (scene->tmap->tex_w);
	else if (hit.hit_type == DOOR)
		return (scene->tmap->door);
	else
		return (scene->tmap->sprite);
}

static double	get_texture_x(t_raycastor	*cast, t_ray_hit	hit) // use Interpolation to blending the color
{
	t_point	hitt;
	double	x;

	if (hit.hit_dir == NORTH || hit.hit_dir == SOUTH)
	{
		hitt.x = (int)floor(hit.hit_x);
		hitt.x %= cast->grid;
		x = (double)hitt.x / cast->grid;
		x = fabs(floor(x * (double)hit.tt_pic.width));
		if (cast->diry < 0)
			x = (double)hit.tt_pic.width - x - 1;
	}
	else
	{
		hitt.y = (int)floor(hit.hit_y);
		hitt.y %= cast->grid;
		x = (double)hitt.y / cast->grid;
		x = fabs(floor(x * (double)hit.tt_pic.width));
		if (cast->dirx > 0)
			x = (double)hit.tt_pic.width - x - 1;
	}
	if (x < 0.0)
		x = 0.0;
	return (x);
}

/* static void	save_door_sprite(t_raycastor	*cast, t_scene *scene)
{

typedef struct s_ray_hit
{
	t_hit	hit_type;
	double	distance;
	t_point	hit_map;//t_point	in_map;
	int		vert_side;
	double	hit_x;
	double	hit_y;
	double	tex_x;
	t_pic	tt_pic;
}	t_ray_hit;

typedef struct s_ray
{
	t_ray_hit	hits[MAX_HITS_PER_RAY];
	int			hit_count;
}	t_ray;

} */

static void	record_hits(t_raycastor	*cast, t_scene *scene, t_ray	*hitps, char	c)
{
	int		n;
	
	if (hitps->hit_count < MAX_HITS_PER_RAY)
	{
		n = hitps->hit_count;
		hitps->hits[n].dist = dist(cast->p.x, cast->p.y, cast->rx, cast->ry);
		hitps->hits[n].hit_type = find_hit_side(cast, c, 0, 1);
		// if (hitps->hits[n].hit_type == DOOR)
		// 	hitps->hits[n].dist *= (1.0 - scene->tmap->door_timer[cast->in_map.y][cast->in_map.x]); // * cast->grid;
		hitps->hits[n].hit_dir = find_hit_side(cast, c, 1, 1);
		hitps->hits[n].hit_map.x = cast->in_map.x;
		hitps->hits[n].hit_map.y = cast->in_map.y;
		hitps->hits[n].vert_side = 1;
		hitps->hits[n].hit_x = cast->rx;
		hitps->hits[n].hit_y = cast->ry;
		hitps->hits[n].tt_pic = find_texture_3d(scene, hitps->hits[n]);
		hitps->hits[n].tex_x = get_texture_x(cast, hitps->hits[n]);
		hitps->hit_count++;
	}
	else
		return ;
}

static int have_repeat(t_point in,  t_ray	*hitps, double	dist)
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

static void	renew_record_hits(t_raycastor	*cast, t_scene *scene, t_ray	*hitps, char	c)
{
	double	dis;
	int		n;
	int		repeat;
	
	if (hitps->hit_count < MAX_HITS_PER_RAY)
	{
		dis = dist(cast->p.x, cast->p.y, cast->rx, cast->ry);
		repeat = have_repeat(cast->in_map, hitps, dis);
		if (repeat == -1)
			return ;
		if (repeat >= 0)
			n = repeat;
		else
		{
			n = hitps->hit_count;
			hitps->hit_count++;
		}
		hitps->hits[n].hit_map.x = cast->in_map.x;
		hitps->hits[n].hit_map.y = cast->in_map.y;
		hitps->hits[n].dist = dis;
		hitps->hits[n].hit_type = find_hit_side(cast, c, 0, 0);
		if (hitps->hits[n].hit_type == DOOR)
			hitps->hits[n].dist += scene->tmap->door_timer[cast->in_map.y][cast->in_map.x] * cast->grid;
		hitps->hits[n].hit_dir = find_hit_side(cast, c, 1, 0);
		hitps->hits[n].vert_side = 0;
		hitps->hits[n].hit_x = cast->rx;
		hitps->hits[n].hit_y = cast->ry;
		hitps->hits[n].tt_pic = find_texture_3d(scene, hitps->hits[n]);
		hitps->hits[n].tex_x = get_texture_x(cast, hitps->hits[n]);
	}
	else
		return ;
}

static int hit_wall_3d(char	**map, int x, int y)
{
	char c;

	c = map[y][x];
	if (c == '0' || c == 'E' || c == 'W' || c == 'N' || c == 'S')
		return (0);
	else
		return (1);
}

void	get_hit_v(t_raycastor	*cast, t_scene *scene, int *depth, t_ray	*hitps)
{
	char	c;
	
	while (*depth < cast->dof)
	{
		cast->in_map.x = scene->tmap->player->posx + floor(cast->rx  / cast->grid) - 5;
		cast->in_map.y = scene->tmap->player->posy + floor(cast->ry  / cast->grid) - 5;
		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
				&& hit_wall_3d(scene->tmap->the_map, cast->in_map.x, cast->in_map.y))
		{
			c = scene->tmap->the_map[cast->in_map.y][cast->in_map.x];
			if (c == '1')
			{
				record_hits(cast, scene, hitps, c);
				*depth = cast->dof;
			}
			else
			{
				record_hits(cast, scene, hitps, c);
				cast->rx += cast->stepx;
        		cast->ry += cast->stepy;
				(*depth)++;
			}
		}
		else
            no_wall(scene, cast, depth);
	}	
}

void	get_hit_h(t_raycastor	*cast, t_scene *scene, int *depth, t_ray	*hits)
{
	char	c;
	
	while (*depth < cast->dof)
	{
		cast->in_map.x = scene->tmap->player->posx + floor(cast->rx  / cast->grid) - 5;
		cast->in_map.y = scene->tmap->player->posy + floor(cast->ry  / cast->grid) - 5;		
		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
				&& hit_wall_3d(scene->tmap->the_map, cast->in_map.x, cast->in_map.y))
		{
			c = scene->tmap->the_map[cast->in_map.y][cast->in_map.x];
			if (c == '1')
			{
				renew_record_hits(cast, scene, hits, c);
				*depth = cast->dof;
			}
			else
			{
				renew_record_hits(cast, scene, hits, c);
				cast->rx += cast->stepx;
        		cast->ry += cast->stepy;
				(*depth)++;
			}
		}
		else
			no_wall(scene, cast, depth);
	}	
}

void	sort_hit_points(t_ray	*hitps)
{
	int	i;
	int j;
	t_ray_hit	tmp;

	i = 0;
	while (i < hitps->hit_count - 1)
	{
		j = i + 1;
		while (j < hitps->hit_count)
		{
			if (hitps->hits[i].dist > hitps->hits[j].dist)
			{
				tmp = hitps->hits[i];
				hitps->hits[i] = hitps->hits[j];
				hitps->hits[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
