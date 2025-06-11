/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:55:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/11 13:58:36 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_out_of_bounds(t_map *map, int x, int y)
{
	return (y < 0 || y >= map->count.map_lines || x < 0
		|| x >= (int)ft_strlen(map->the_map[y]));
}

static void	flood_fill(t_map *map, int x, int y, char **lines)
{
	if (is_out_of_bounds(map, x, y))
	{
		ft_split_free(lines);
		ft_split_free(map->map_copy);
		perror_and_exit(map, "Map not closed (out of bounds)");
	}
	if (ft_isspace(map->map_copy[y][x]) || map->map_copy[y][x] == '\0')
	{
		ft_split_free(lines);
		ft_split_free(map->map_copy);
		perror_and_exit(map, "Map not closed (space leak)");
	}
	if (map->map_copy[y][x] == '1' || map->map_copy[y][x] == '3'
		|| map->map_copy[y][x] == 'v')
		return ;
	map->map_copy[y][x] = 'v';
	flood_fill(map, x + 1, y, lines);
	flood_fill(map, x - 1, y, lines);
	flood_fill(map, x, y + 1, lines);
	flood_fill(map, x, y - 1, lines);
}

bool	is_closed_map(t_map	*map, char **lines)
{
	map->map_copy = ft_tabdup(map->the_map);
	if (!map->map_copy)
		return (ft_split_free(lines),
			perror_and_exit(map, "Malloc failed"), false);
	flood_fill(map, map->player.posx, map->player.posy, lines);
	ft_split_free(map->map_copy);
	return (true);
}
