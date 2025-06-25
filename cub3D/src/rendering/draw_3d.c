/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:09:52 by  layang           #+#    #+#             */
/*   Updated: 2025/06/24 18:56:55 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	renew_zbuffer(t_scene	*s, t_ray_hit	hit, int r)
{
	int		hp;

	hp = s->tmap->door_state[hit.hit_map.y][hit.hit_map.x];
	if (hp == DOOR_CLOSED || hp == DOOR_OPENING || hp == DOOR_CLOSING)
		s->tmap->player->zbuffer[r] = hit.dist;
}

static void	save_sprite_status(t_scene *scene, t_ray_hit	hit)
{
	int	i;
	t_cam	*player;

	player = scene->tmap->player;
	i = player->nb_sprites;
	if (i >= MAX_HITS_PER_RAY)
		return ;
	i = 0;
	while (i < player->nb_sprites)
	{
		if (player->sprites[i].x == hit.hit_map.x 
				&& player->sprites[i].y == hit.hit_map.y)
			return ;
		i++;
	}
	i = player->nb_sprites;
	player->sprites[i].x = hit.hit_map.x;
	player->sprites[i].y = hit.hit_map.y;
	player->nb_sprites++;
}

static void draw_pix_column(t_ray	*hitps, t_raycastor	*cast, t_scene *scene)
{
	int		i;
	t_hit	h;

	sort_hit_points(hitps);
	i = hitps->hit_count - 1;
	while (i >= 0)
	{
		h = hitps->hits[i].hit_type;
		if (i == hitps->hit_count - 1)
			scene->tmap->player->zbuffer[cast->this_r] = hitps->hits[i].dist;
		if (h == NORTH || h == SOUTH || h == EAST || h == WEST)
			draw_wall_column(cast, scene, hitps->hits[i]);
		else if (h == DOOR)
		{
			draw_door_height(cast, scene, hitps->hits[i]);
			if (i - 1 >= 0 && hitps->hits[i - 1].hit_type == SPRITE)
				renew_zbuffer(scene, hitps->hits[i], cast->this_r);
		}
		else if (h == SPRITE)
			save_sprite_status(scene, hitps->hits[i]);
		i--;
	}
}

static void	dda_raycasting_3d(t_raycastor	*cast, t_scene *s, int r, t_point p)
{
	double	off_r;
	int		depth;
	int		n;
	t_ray	hitps;

	n = s->tmap->player->ray_nb;
	off_r = ((double)r / (n - 1)) * cast->fov - (cast->fov / 2.0);
	cast->ra = normalize_angle(s->tmap->player->p_angle + off_r);
	cast->this_r = r;
	//init_raycastor(p, cast);
	cast->dirx = cos(cast->ra);
	cast->diry = sin(cast->ra);
	cast->p = p;
	hitps.hit_count = 0;
	hitps.distW = 0.0;
	intersect_v(cast, p, &depth);
	get_hit_v(cast, s, &depth, &hitps);
	intersect_h(cast, p, &depth);
	get_hit_h(cast, s, &depth, &hitps);
	draw_pix_column(&hitps, cast, s);
}

void	draw_3d_scene(t_scene *scene, t_point p, int grid, t_point	off)
{
	t_raycastor	*cast;
	int			r;
	int			n;

	cast = scene->tmap->player->ray2;
	cast->ra = scene->tmap->player->p_angle;
	cast->fov = scene->tmap->player->fov;
	cast->dof = fmax(scene->tmap->count.map_lines,
		scene->tmap->count.map_width);
	cast->grid = grid;
	r = 0;
	p.x -= off.x;
	p.y -= off.y;
	cast->offset.x = off.x;
	cast->offset.y = off.y;
	n = scene->tmap->player->ray_nb;
	cast->pix_ray = WIDTH / scene->tmap->player->ray_nb;
	clear_zbuffer_sprites(scene->tmap->player);
	while (r < n)
	{
		dda_raycasting_3d(cast, scene, r, p);
		r++;
	}
	sort_draw_sprites(scene, p);
}
