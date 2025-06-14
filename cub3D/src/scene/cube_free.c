/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:21:11 by layang            #+#    #+#             */
/*   Updated: 2025/06/11 13:51:13 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_arr(char	***paths)
{
	int	i;

	i = 0;
	if (!paths || !*paths || !**paths)
		return ;
	while ((*paths)[i])
	{
		if ((*paths)[i])
			free((*paths)[i]);
		i++;
	}
	free(*paths);
	*paths = NULL;
}

void	free_lst(t_lmap	**tokens)
{
	t_lmap	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = *tokens;
		if (tmp->line)
		{
			free(tmp->line);
			tmp->line = NULL;
		}
		*tokens = (*tokens)->next;
		free(tmp);
	}
	*tokens = NULL;
}

int	close_cube3d(t_scene	*scene)
{
	mlx_destroy_window(scene->mlx, scene->win);
	scene->win = NULL;
	mlx_destroy_image(scene->mlx, scene->img.mlx_img);
	mlx_destroy_image(scene->mlx, scene->tmap->tex_n);
	mlx_destroy_image(scene->mlx, scene->tmap->tex_s);
	mlx_destroy_image(scene->mlx, scene->tmap->tex_w);
	mlx_destroy_image(scene->mlx, scene->tmap->tex_e);
	if (scene->tmap->door)
		mlx_destroy_image(scene->mlx, scene->tmap->door);
	if (scene->tmap->sprite)
		mlx_destroy_image(scene->mlx, scene->tmap->sprite);
	mlx_destroy_display(scene->mlx);
	free_arr(&scene->tmap->the_map);
	free_lst(&scene->tmap->lmap);
	free_map_data(scene->tmap);
	free(scene->mlx);
	exit (0);
    return (0);
}
