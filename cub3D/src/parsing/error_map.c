/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:47:49 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/23 11:42:33 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	close_not_img(t_scene *scene)
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
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
	exit (1);
	return (0);
}

void	perror_and_exit(t_scene *scene, char *str)
{
	if (str)
		printf("Error!\n%s\n", str);
	if (scene)
		close_not_img(scene);
}

void	print_err(char *str)
{
	printf("Error!\n");
	if (str)
		printf("%s\n", str);
}
