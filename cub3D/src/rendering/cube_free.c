/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:21:11 by layang            #+#    #+#             */
/*   Updated: 2025/06/25 23:21:02 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_arr(void	***paths)
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

/* void	free_lst(t_lmap	**tokens)
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
} */

int	close_cube3d(t_scene *scene)
{
	if (!scene)
		return (0);
	if (scene->win)
	{
		mlx_destroy_window(scene->mlx, scene->win);
		scene->win = NULL;
	}
	if (scene->tmap)
	{
		free_map_img(scene);
		free_map_data(scene->tmap);
	}
	if (scene && scene->img.mlx_img)
		mlx_destroy_image(scene->mlx, scene->img.mlx_img);
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
	exit (1);
	return (0);
}
