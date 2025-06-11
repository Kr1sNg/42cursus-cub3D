/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/11 13:54:21 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	check_img(void *mlx, void **image, char *path)
{
	int	width;
	int	height;

	*image = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!(*image))
		return (false);
	return (true);
}

static bool img_init(void *mlx, t_map *tmap)
{
	if (!check_img(mlx, &tmap->tex_e, tmap->path_e)
		|| !check_img(mlx, &tmap->tex_n, tmap->path_n) 
		|| !check_img(mlx, &tmap->tex_s, tmap->path_s)
		|| !check_img(mlx, &tmap->tex_w, tmap->path_w)
		|| !check_img(mlx, &tmap->door, "textures/door.xpm")
		|| !check_img(mlx, &tmap->sprite, "textures/sprite.xpm"))
		return (false);
	return (true);
}

static void player_init(t_map *tmap)
{
	tmap->player.planex = 0.66;
	tmap->player.planey = 0;
	tmap->player.pitch = 0;
	tmap->player.p_angle = get_player_angle(tmap->player);
	tmap->player.fov = 66.0;
	tmap->player.ray_nb = 240;
}

t_map	*map_init(void *mlx, char *path)
{
	t_map	*tmap;
	
	tmap = ft_calloc(1, sizeof(t_map));
	if (!tmap)
		return (perror("Error\nMalloc failed\n"), NULL);
	ft_parsing(path, tmap);
	if (!img_init(mlx, tmap))
		return (perror_and_exit(tmap, "Cannot load image"), NULL);
	player_init(tmap);
	return (tmap);
}


