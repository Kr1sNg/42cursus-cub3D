/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/26 15:51:21 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	animated_sprit_2(int sign, void	*mlx, t_map	*tmap)
{
	if (sign == 0)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly1.xpm"))
			return (false);
	}
	else if (sign == 1)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly2.xpm"))
			return (false);
	}
	else if (sign == 2)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly3.xpm"))
			return (false);
	}
	else if (sign == 3)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly4.xpm"))
			return (false);
	}
	return (true);
}

bool	animated_sprit(void	*mlx, t_map	*tmap)
{
	int	sp;

	sp = 4;
	if (tmap->count.animation > 3 * sp)
		tmap->count.animation = 0;
	if (tmap->sprite.mlx_img)
		mlx_destroy_image(mlx, tmap->sprite.mlx_img);
	if (!animated_sprit_2(tmap->count.animation / sp, mlx, tmap))
		return (false);
	return (tmap->count.animation++, true);
}
