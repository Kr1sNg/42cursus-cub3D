/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:23:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 13:09:17 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_map_block(t_map *map, char **lines)
{
	int	i;

	i = 0;
	while (lines && lines[i])
	{
		if (!is_map_line(lines[i]))
			break ;
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

int	is_valid_map(t_map *map, char **lines)
{
	if (!has_located_player(map))
		return (false);
	if (!is_closed_map(map, lines))
		return (false);
	return (true);
}
