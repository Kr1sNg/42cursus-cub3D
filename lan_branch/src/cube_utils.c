/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:24:16 by layang            #+#    #+#             */
/*   Updated: 2025/06/07 14:25:28 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_3d.h"

void	put_pixel(t_pic	*img, t_point	pt)
{
	char	*dst;
	int		x;
	int		y;

	x = round(pt.x);
	y = round(pt.y);
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_pix / 8));
	*(unsigned int *)dst = pt.color;
}

void	render_background(t_pic	*img, t_map	*tmap)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(img, (t_point){j, i, tmap->color_c});
			j++;
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(img, (t_point){j, i, tmap->color_f});
			j++;
		}
		i++;
	}
}

void	translate(t_map	*tmap, t_point	mov)
{
	int		x;
	int		y;
	char	c;

	x = tmap->player.posx + mov.x;
	y = tmap->player.posy + mov.y;
	if (x >= 0 && y >= 0 && x < tmap->map_w
		&& y < tmap->map_h
		&& x < (int)ft_strlen(tmap->map[y]))
	{
		c = tmap->map[y][x];
		if (c && (c == '0' || c == 'N' || c == 'S'
				|| c == 'E' || c == 'W'))
		{
			tmap->player.posx = x;
			tmap->player.posy = y;
		}
	}
}
