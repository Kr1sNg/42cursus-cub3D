/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:09:52 by  layang           #+#    #+#             */
/*   Updated: 2025/06/18 16:50:42 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_pix_column(int r, t_raycastor	*cast, t_scene *scene)
{
	int	i;
	int	start;
	int	j;

	start = WIDTH - r * cast->pix_ray - 1;
	i = WIDTH - r * cast->pix_ray - 1;
	cast->step_tt = 64.0 / cast->ori_rend_h;
	while (i > start - cast->pix_ray)
	{
		j = 0;
		while (j < cast->draw_off)
		{
			put_pixel(&scene->img, (t_point){i, j, scene->tmap->color_c});
			j++;
		}
		put_pixel_texture(scene, (t_point){i, j, PURPLE}, cast);
		j += cast->rend_h;
		while (j < HEIGHT)
		{
			put_pixel(&scene->img, (t_point){i, j, scene->tmap->color_f});
			j++;
		}
		i--;
	}	
}

void	get_correct_dist(t_raycastor	*cast)
{
    if (cast->disV < cast->disH)
	{
		cast->final_x = cast->vx;
		cast->final_y = cast->vy;
		cast->hit = cast->vhit;
		cast->dist = cast->disV;
	}
	else
	{
		cast->final_x = cast->hx;
		cast->final_y = cast->hy;
		cast->hit = cast->hhit;
		cast->dist = cast->disH;
	}
}

static void	draw_ray_3d(t_raycastor	*cast, t_scene *scene, int r, double ra)
{			
	double	ca;
	double	no_fisheye_dist;
	double	proj_plane_dist;
	
	get_correct_dist(cast);
	ca = normalize_angle(scene->tmap->player->p_angle - ra);
	no_fisheye_dist = cast->dist * cos(ca);
	proj_plane_dist = (WIDTH / 2.0) / tan(scene->tmap->player->fov / 2.0);
	cast->rend_h = (int)((cast->grid / no_fisheye_dist) * proj_plane_dist);
	cast->ori_rend_h = cast->rend_h;
	if (cast->rend_h > HEIGHT)
		cast->rend_h = HEIGHT;
	cast->ori_off = (HEIGHT - cast->rend_h) / 2;
	cast->draw_off = floor((1.0 - scene->tmap->player->pitch) * cast->ori_off);
	draw_pix_column(r, cast, scene);
}

static void dda_raycasting_3d(t_raycastor	*cast, t_scene *s, int r, t_point p)
{
    double	off_r;
	int		depth;
	int		n;

    n = s->tmap->player->ray_nb;
    off_r = ((double)r / (n - 1)) * cast->fov - (cast->fov / 2.0);
    cast->ra = normalize_angle(s->tmap->player->p_angle + off_r);
    init_raycastor(p, cast);
    cast->dirx = cos(cast->ra);
    cast->diry = sin(cast->ra);
    intersect_h(cast, p, &depth);
    get_dis_h(cast, s, p, &depth);
    intersect_v(cast, p, &depth);
    get_dis_v(cast, s, p, &depth);
    draw_ray_3d(cast, s, r, cast->ra);
}

void	draw_3d_scene(t_scene *scene, t_point p, int grid, t_point	off)
{
	t_raycastor	*cast;
	int		r;
	int		n;
    
	cast = scene->tmap->player->ray2;
	cast->ra = scene->tmap->player->p_angle;
	cast->fov = scene->tmap->player->fov;
	cast->dof = fmax(scene->tmap->count.map_lines, scene->tmap->count.map_width);
	cast->grid = grid;
	r = 0;
	p.x -= off.x;
	p.y -= off.y;
	cast->offset.x = off.x;
	cast->offset.y = off.y;
	n = scene->tmap->player->ray_nb;
	cast->pix_ray = WIDTH / scene->tmap->player->ray_nb;
	while (r < n)
	{
		dda_raycasting_3d(cast, scene, r, p);
		r++;
	}
}
