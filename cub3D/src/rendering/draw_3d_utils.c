/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:38:00 by layang            #+#    #+#             */
/*   Updated: 2025/06/24 17:51:01 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall_column(t_raycastor	*cast, t_scene *scene, t_ray_hit	hit)
{
	int	i;
	int	start;
	int	j;

	get_render_height(cast, scene, hit);
	start = WIDTH - cast->this_r * cast->pix_ray - 1;
	i = start;
	cast->step_tt = (double)hit.tt_pic.height / cast->ori_rend_h;
	while (i > start - cast->pix_ray)
	{
		j = 0;
		while (j < cast->draw_off)
		{
			put_pixel(&scene->img, (t_point){i, j, scene->tmap->color_c});
			j++;
		}
		texture_3d(scene, (t_point){i, j, PURPLE}, cast, hit);
		j += cast->rend_h;
		while (j < HEIGHT)
		{
			put_pixel(&scene->img, (t_point){i, j, scene->tmap->color_f});
			j++;
		}
		i--;
	}	
}

void	draw_door_height(t_raycastor	*cast, t_scene *scene, t_ray_hit	hit)
{
	int	i;
	int	start;
	int	j;

	get_render_height(cast, scene, hit);
	start = WIDTH - cast->this_r * cast->pix_ray - 1;
	i = start;
	cast->step_tt = (double)hit.tt_pic.height / cast->ori_rend_h;
	while (i > start - cast->pix_ray)
	{
		j = cast->draw_off;
		texture_3d(scene, (t_point){i, j, PURPLE}, cast, hit);
		i--;
	}	
}

void	clear_zbuffer_sprites(t_cam *player)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		player->zbuffer[i] = 0.0;
		i++;
	}
	i = 0;
	while (i < MAX_HITS_PER_RAY)
	{
		player->sprites[i].x = 0;
		player->sprites[i].y = 0;
		player->sprites[i].color = 0;
		i++;
	}
	player->nb_sprites = 0;
}

static void    cut_hits_by_wall(t_ray	*hitps)
{
    t_hit	h;
    int     i;

    i = 0;
	while (i < hitps->hit_count)
	{
		h = hitps->hits[i].hit_type;
		if (h == NORTH || h == SOUTH || h == EAST || h == WEST)
			break ;
		i++;
	}
	hitps->hit_count = i + 1;
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
    cut_hits_by_wall(hitps);
}
