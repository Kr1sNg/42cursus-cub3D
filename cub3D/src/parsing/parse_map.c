/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:23:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/23 11:43:58 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_map_block(t_map *map, char **lines)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (lines && lines[i])
	{
		if (!is_map_line(lines[i]))
			break ;
		len = ft_strlen(lines[i]);
		if (len > map->count.map_width)
			map->count.map_width = len;
		i++;
	}
	map->count.map_lines = i;
	map->the_map = ft_calloc(i + 1, sizeof(char *));
	if (!map->the_map)
		return (-42);
	i = -1;
	while (++i < map->count.map_lines)
		map->the_map[i] = ft_strtrim((lines[i]), "\n");
	return (i);
}

int	is_valid_map(t_map *tmap, char **lines)
{
	if (!has_located_player(tmap))
		return (print_err("Invalid player"), false);
	if (!tmap->count.player_count)
		return (print_err("Invalid number of player"), false);
	if (!is_closed_map(tmap, lines))
		return (print_err("Invalid map block"), false);
	if (tmap->count.c_line != 1 || tmap->count.f_line != 1
		|| tmap->count.ea_line != 1 || tmap->count.no_line != 1
		|| tmap->count.so_line != 1 || tmap->count.we_line != 1)
		return (print_err("Missing element"), false);
	return (true);
}
