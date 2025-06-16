/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:04:01 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/16 11:54:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	color_toi(char **split)
{
	int	value;
	int	ri;
	int	gi;
	int	bi;

	if (!split || !split[0] || !split[1] || !split[2] || !split[3])
		return (-42);
	ri = ft_atoi(split[1]);
	gi = ft_atoi(split[2]);
	bi = ft_atoi(split[3]);
	if ((0 > ri || ri > 255) || (0 > gi || gi > 255) || (0 > bi || bi > 255))
		return (-42);
	value = ((ri << 16) | (gi << 8) | bi);
	return (value);
}

void	print_map(t_scene *scene)
{
	int	i;

	if (!scene->tmap || !scene->tmap->the_map)
		perror_and_exit(scene, "NO MAP!");
	i = -1;
	while (scene->tmap->the_map && scene->tmap->the_map[++i])
		printf("map[%i]: [%s]\n", i, scene->tmap->the_map[i]);
}
