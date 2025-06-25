/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 07:09:10 by marvin            #+#    #+#             */
/*   Updated: 2025/06/25 19:03:12 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	add_hit_cast(t_raycastor	*cast, int n, char c, t_ray	*hitps)
{
	int	vert;

	vert = hitps->hits[n].vert_side;
	hitps->hits[n].hit_map.x = cast->in_map.x;
	hitps->hits[n].hit_map.y = cast->in_map.y;
	hitps->hits[n].hit_type = find_hit_side(cast, c, 0, vert);
	hitps->hits[n].hit_dir = find_hit_side(cast, c, 1, vert);
	hitps->hits[n].hit_x = cast->rx;
	hitps->hits[n].hit_y = cast->ry;
}

void	renew_hits(t_raycastor	*cast, t_scene	*s, t_ray	*hitps, char c)
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
		hitps->hits[n].dist = dis;
		hitps->hits[n].vert_side = 0;
		add_hit_cast(cast, n, c, hitps);
		hitps->hits[n].tt_pic = find_texture_3d(s, hitps->hits[n]);
		hitps->hits[n].tex_x = get_texture_x(cast, hitps->hits[n]);
	}
	else
		return ;
}

void	record_hits(t_raycastor	*cast, t_scene	*sc, t_ray	*hitps, char c)
{
	int	n;

	if (hitps->hit_count < MAX_HITS_PER_RAY)
	{
		n = hitps->hit_count;
		hitps->hits[n].dist = dist(cast->p.x, cast->p.y, cast->rx, cast->ry);
		hitps->hits[n].vert_side = 1;
		add_hit_cast(cast, n, c, hitps);
		hitps->hits[n].tt_pic = find_texture_3d(sc, hitps->hits[n]);
		hitps->hits[n].tex_x = get_texture_x(cast, hitps->hits[n]);
		hitps->hit_count++;
	}
	else
		return ;
}

void	get_hit_v(t_raycastor	*cast, t_scene	*sc, int	*depth, t_ray	*hs)
{
	char	c;

	while (*depth < cast->dof)
	{
		renew_pos_in_map(sc, cast);
		if (inside_map_array(cast->in_map.x, cast->in_map.y, sc)
			&& hit_wall(sc->tmap, cast->in_map, 1))
		{
			c = sc->tmap->the_map[cast->in_map.y][cast->in_map.x];
			if (c == '1')
			{
				record_hits(cast, sc, hs, c);
				*depth = cast->dof;
			}
			else
			{
				record_hits(cast, sc, hs, c);
				cast->rx += cast->stepx;
				cast->ry += cast->stepy;
				(*depth)++;
			}
		}
		else
			no_wall(sc, cast, depth);
	}
}

void	get_hit_h(t_raycastor	*cast, t_scene	*sc, int	*depth, t_ray	*hs)
{
	char	c;

	while (*depth < cast->dof)
	{
		renew_pos_in_map(sc, cast);
		if (inside_map_array(cast->in_map.x, cast->in_map.y, sc)
			&& hit_wall(sc->tmap, cast->in_map, 1))
		{
			c = sc->tmap->the_map[cast->in_map.y][cast->in_map.x];
			if (c == '1')
			{
				renew_hits(cast, sc, hs, c);
				*depth = cast->dof;
			}
			else
			{
				renew_hits(cast, sc, hs, c);
				cast->rx += cast->stepx;
				cast->ry += cast->stepy;
				(*depth)++;
			}
		}
		else
			no_wall(sc, cast, depth);
	}
}
