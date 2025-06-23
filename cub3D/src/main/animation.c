/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/23 09:42:31 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	animated_sprit(void *mlx, t_map *tmap)
{
	if (tmap->count.animation > 3)
		tmap->count.animation = 0;
	if (tmap->sprite.mlx_img)
		mlx_destroy_image(mlx, tmap->sprite.mlx_img);
	if (tmap->count.animation == 0)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly1.xpm"))
			return (false);
	}
	else if (tmap->count.animation == 1)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly2.xpm"))
			return (false);
	}
	else if (tmap->count.animation == 2)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly3.xpm"))
			return (false);
	}
	else if (tmap->count.animation == 3)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly4.xpm"))
			return (false);
	}
	return (tmap->count.animation++, true);
}
