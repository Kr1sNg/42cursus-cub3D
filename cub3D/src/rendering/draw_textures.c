/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:00:40 by layang            #+#    #+#             */
/*   Updated: 2025/06/19 17:27:29 by tat-nguy         ###   ########.fr       */
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
	else if (cast->hit == DOOR && cast->dist > 60)
		return (scene->tmap->door);
	else if (cast->hit == DOOR && cast->dist <= 60)
		return (scene->tmap->door2);
	else
		return (scene->tmap->sprite);
}

static int	get_color_at(t_pic *img, int x, int y)
{
	char *pixel;
	int color;

	pixel = img->addr + (y * img->line_len + x * (img->bits_pix / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

static double	hit_texture_x(t_raycastor	*cast) // use Interpolation to blending the color
{
	t_point	hitt;
	double	x;

	if (cast->hit_dir == NORTH || cast->hit_dir == SOUTH)
	{
		hitt.x = (int)floor(cast->final_x);
		hitt.x %= cast->grid;
		x = (double)hitt.x / cast->grid;
		x = fabs(floor(x * (double)cast->tt_pic.width));
		if (cast->diry < 0)
			x = (double)cast->tt_pic.width - x - 1;
	}
	else
	{
		hitt.y = (int)floor(cast->final_y);
		hitt.y %= cast->grid;
		x = (double)hitt.y / cast->grid;
		x = fabs(floor(x * (double)cast->tt_pic.width));
		if (cast->dirx > 0)
			x = (double)cast->tt_pic.width - x - 1;
	}
	return (x);
}

void	put_pixel_texture(t_scene	*scene, t_point	po, t_raycastor	*cast)
{
	double	x;
	double	y;
	int		 i;

	i = 0;
	x = hit_texture_x(cast);
	y = 0.0;
	while (i < cast->rend_h)
	{
		po.color = get_color_at(&cast->tt_pic, (int)x, (int)y);
		put_pixel(&scene->img, po);
		y += cast->step_tt;
		po.y++;
		i++;
	}
}
