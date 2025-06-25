/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:24:16 by layang            #+#    #+#             */
/*   Updated: 2025/06/25 18:36:51 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// change color s to color e by a ratio r, can use to change color transparence 
int	gradient_color(float_t r, int s, int e)
{
	int		rgb[3];

	rgb[0] = (int)roundf((1 - r) * ((s >> 16) & 0xFF) + r * ((e >> 16) & 0xFF));
	rgb[1] = (int)roundf((1 - r) * ((s >> 8) & 0xFF) + r * ((e >> 8) & 0xFF));
	rgb[2] = (int)roundf((1 - r) * (s & 0xFF) + r * (e & 0xFF));
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0)
		angle += 2.0 * M_PI;
	return (angle);
}

double	get_player_angle(t_map *tmap)
{
	double	angle_radian;

	angle_radian = -atan2(tmap->count.map_diry, tmap->count.map_dirx);
	if (angle_radian < 0)
		angle_radian += 2.0 * M_PI;
	return (angle_radian);
}

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

double	sp_dist(t_cam *player, t_point	po, t_point	s, int n)
{
	double	ox;
	double	oy;
	double	dis;
	int		gr;

	ox = player->ray2->offx;
	oy = player->ray2->offy;
	gr = player->ray2->grid;
	if (n == 1)
		return (s.x * gr -(po.x * gr + ox));
	else if (n == 2)
		return (s.y * gr -(po.y * gr + oy));
	else
	{
		dis = dist(s.x * gr, s.y * gr, po.x * gr + ox, po.y * gr + oy);
		return (dis);
	}
}
