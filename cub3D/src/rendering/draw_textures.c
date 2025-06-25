/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:00:40 by layang            #+#    #+#             */
/*   Updated: 2025/06/24 18:57:36 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_pic	find_texture_xpm(t_scene	*scene, t_raycastor	*cast)
{	
	if (cast->hit == DEFAULT)
		return ((t_pic){NULL, NULL, 0, 0, 0, 0, 0});
	else if (cast->hit == NORTH)
		return (scene->tmap->tex_n);
	else if (cast->hit == SOUTH)
		return (scene->tmap->tex_s);
	else if (cast->hit == EAST)
		return (scene->tmap->tex_e);
	else if (cast->hit == WEST)
		return (scene->tmap->tex_w);
	else if (cast->hit == DOOR)
		return (scene->tmap->door);
	else
		return (scene->tmap->sprite);
}

int	get_color_at(t_pic *img, int x, int y)
{
	char *pixel;
	int color;

	pixel = img->addr + (y * img->line_len + x * (img->bits_pix / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

double	get_texture_x(t_raycastor	*cast, t_ray_hit	hit)
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

static	void renew_x_door(double *x, t_scene	*scene, t_ray_hit	hit)
{
	double	t;
	
	t = scene->tmap->door_timer[hit.hit_map.y][hit.hit_map.x];
	*x -= t * hit.tt_pic.width;
}

void	texture_3d(t_scene	*scene, t_point	po, t_raycastor	*cast, t_ray_hit	hit)
{
	double	x;
	double	y;
	int		 i;

	i = 0;
	x = hit.tex_x;
	if (hit.hit_type == DOOR)
	{
		renew_x_door(&x, scene, hit);
		if (x < 0)
			return ;
	}
	y = 0.0;
	if (hit.tt_pic.mlx_img && (cast->ori_rend_h > cast->rend_h))
		y += (hit.tt_pic.height * (cast->ori_rend_h - cast->rend_h)) 
			/ (2.0 * cast->ori_rend_h);
	while (i < cast->rend_h)
	{
		if (hit.tt_pic.mlx_img)
			po.color = get_color_at(&hit.tt_pic, (int)x, (int)y);
		put_pixel(&scene->img, po);
		y += cast->step_tt;
		po.y++;
		i++;
	}
}
