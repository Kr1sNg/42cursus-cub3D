/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:04:01 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 10:37:59 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	color_toi(t_map *map, char **split, char **lines)
{
	int	value;
	int	ri;
	int	gi;
	int	bi;

	if (!split || !split[0] || !split[1] || !split[2] || !split[3])
		return (ft_split_free(lines), ft_split_free(split),
			perror_and_exit(map, "Invalid color"), -42);
	ri = ft_atoi(split[1]);
	gi = ft_atoi(split[2]);
	bi = ft_atoi(split[3]);
	printf("rgb collor in int: %i, %i, %i\n", ri, gi, bi);
	if ((0 > ri || ri > 255) || (0 > gi || gi > 255) || (0 > bi || bi > 255))
		return (ft_split_free(lines), ft_split_free(split),
			perror_and_exit(map, "Invalid color value"), -42);
	value = ((ri << 16) | (gi << 8) | bi);
	return (value);
}

void	print_map(t_map *map)
{
	int	i;

	if (!map || !map->the_map)
		perror_and_exit(map, "NO MAP!");
	i = -1;
	while (map->the_map && map->the_map[++i])
		printf("map[%i]: [%s]\n", i, map->the_map[i]);
}
