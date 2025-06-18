/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:00:40 by layang            #+#    #+#             */
/*   Updated: 2025/06/18 17:08:09 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_pic	find_texture_xpm(t_scene	*scene, t_raycastor	*cast)
{	
	if (cast->hit == DEFAULT)
		return ((t_pic){NULL, NULL, 0, 0, 0, 0, 0});
	else if (cast->hit == NORTH)
		return (scene->tmap->tex_n);
	else if (cast->hit == SOUTH)
		return (scene->tmap->tex_s);
	else if (cast->hit == EAST)
		return (scene->tmap->tex_e);
	else
		return (scene->tmap->tex_w);
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

	if (cast->hit == NORTH || cast->hit == SOUTH)
	{
		hitt.x = (int)floor(cast->final_x);
		hitt.x %= cast->grid;
		x = (double)hitt.x / cast->grid;
		x = fabs(floor(x * 64.0));
		if (cast->diry < 0)
			x = 64.0 - x - 1;
	}
	else
	{
		hitt.y = (int)floor(cast->final_y);
		hitt.y %= cast->grid;
		x = (double)hitt.y / cast->grid;
		x = fabs(floor(x * 64.0));
		if (cast->dirx > 0)
			x = 64.0 - x - 1;
	}
	return (x);
}

void	put_pixel_texture(t_scene	*scene, t_point	po, t_raycastor	*cast)
{
	t_pic	tt_pic;
	double	x;
	double	y;
	int		 i;

	tt_pic = find_texture_xpm(scene, cast);
	if (!tt_pic.mlx_img)  // put_default_col(po, cast, scene);
	{
		printf("MAP not found.\n");
		i = 0;
		while (i < cast->rend_h)
		{
			put_pixel(&scene->img, po);
			po.y++;
			i++;
		}
		return ;
	}
	i = 0;
	x = hit_texture_x(cast);
	y = 0.0;
	while (i < cast->rend_h)
	{
		po.color = get_color_at(&tt_pic, (int)x, (int)y);
		put_pixel(&scene->img, po);
		y += cast->step_tt;
		po.y++;
		i++;
	}
}
