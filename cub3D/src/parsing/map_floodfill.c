/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:55:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/17 10:49:11 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_out_of_bounds(t_map *map, int x, int y)
{
	return (y < 0 || y >= map->count.map_lines || x < 0
		|| x >= (int)ft_strlen(map->the_map[y]));
}

static void	flood_fill(t_map *tmap, int x, int y, char **lines)
{
	if (is_out_of_bounds(tmap, x, y))
	{
		ft_split_free(lines);
		ft_split_free(tmap->map_copy);
		print_err("Map not closed (out of bounds)");
		free_map_data(tmap);
		exit(1);
	}
	if (ft_isspace(tmap->map_copy[y][x]) || tmap->map_copy[y][x] == '\0')
	{
		ft_split_free(lines);
		ft_split_free(tmap->map_copy);
		print_err("Map not closed (space leak)");
		free_map_data(tmap);
		exit(1);
	}
	if (tmap->map_copy[y][x] == '1' || tmap->map_copy[y][x] == '3'
		|| tmap->map_copy[y][x] == 'v')
		return ;
	tmap->map_copy[y][x] = 'v';
	flood_fill(tmap, x + 1, y, lines);
	flood_fill(tmap, x - 1, y, lines);
	flood_fill(tmap, x, y + 1, lines);
	flood_fill(tmap, x, y - 1, lines);
}

bool	is_closed_map(t_map *tmap, char **lines)
{
	tmap->map_copy = ft_tabdup(tmap->the_map);
	if (!tmap->map_copy)
		return (ft_split_free(lines), print_err("Malloc failed"), false);
	flood_fill(tmap, tmap->player.posx, tmap->player.posy, lines);
	ft_split_free(tmap->map_copy);
	return (true);
}
