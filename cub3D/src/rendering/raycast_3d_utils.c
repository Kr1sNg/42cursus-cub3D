/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3d_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:02:25 by layang            #+#    #+#             */
/*   Updated: 2025/06/24 17:44:28 by layang           ###   ########.fr       */
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

static int hit_wall_3d(char	**map, int x, int y)
{
	char c;

	c = map[y][x];
	if (c == '0' || c == 'E' || c == 'W' || c == 'N' || c == 'S')
		return (0);
	else
		return (1);
}

static void renew_pos_in_map(t_scene *scene, t_raycastor	*cast)
{
	cast->in_map.x = scene->tmap->player->posx + floor(cast->rx  / cast->grid) - 5;
	cast->in_map.y = scene->tmap->player->posy + floor(cast->ry  / cast->grid) - 5;
}
 
void	get_hit_v(t_raycastor	*cast, t_scene *scene, int *depth, t_ray	*hitps)
{
	char	c;
	
	while (*depth < cast->dof)
	{
		renew_pos_in_map(scene, cast);
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
		renew_pos_in_map(scene, cast);		
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
