/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:55:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/08 12:36:13 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_out_of_bounds(t_map *map, int x, int y)
{
	// printf("posx: %i, posy: %i\n", x, y);
	return (y < 0 || y >= map->count.map_lines || x < 0
				|| x >= (int)ft_strlen(map->the_map[y]));
}

static void	flood_fill(t_map *map, char **copy, int x, int y)
{
	if (is_out_of_bounds(map, x, y))
	{
		free(copy);
		free_map_data(map);
		exit(print_error("Map not closed (out of bounds)"));
	}
	if (ft_isspace(copy[y][x]) || copy[y][x] == '\0')
	{
		free(copy);
		free_map_data(map);
		exit(print_error("Map not closed (space leak)"));
	}
	if (copy[y][x] == '1' || copy[y][x] == 'v')
		return ;
	copy[y][x] = 'v';
	flood_fill(map, copy, x + 1, y);
	flood_fill(map, copy, x - 1, y);
	flood_fill(map, copy, x, y + 1);
	flood_fill(map, copy, x, y - 1);
}

bool	is_closed_map(t_map	*map)
{
	char	**copy;

	copy = ft_tabdup(map->the_map);
	if (!copy)
		return (print_error("Malloc failed"), false);
	
	flood_fill(map, copy, map->posx, map->posy);
	ft_split_free(copy);
	return (true);
}
