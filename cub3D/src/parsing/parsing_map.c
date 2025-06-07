/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:23:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/07 10:05:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* fill-in information for:
	1 - char	**map;
	
	2 - int		posx;
		int		posy;
	
	3 - int		dirx; (direction of player)
		int		diry;
*/

void	parse_map_block(char **line, t_map *map)
{
	int	i;

	i = 0;
	
	while (line[i])
	{
		if (!is_map_line(line[i]))
			exit(print_error("empty line in map"));
		i++;
	}
	map->count.map_lines = i;
	map->the_map = ft_calloc(i + 1, sizeof(char *));
	if (!map->the_map)
		exit(print_error("Malloc failed"));
	i = -1;
	while (++i < map->count.map_lines)
		map->the_map[i] = ft_strdup(line[i]);
	if (!is_valid_map(map->the_map))
		exit(print_error("Invalid THE map!"));
}

void	print_map(char **map)
{
	int	i;
	
	i = -1;
	while (map && map[++i])
		printf("map[%i]: [%s]\n", i, map[i]);
}

int	is_valid_map(char **map)
{
	if (!is_bordered(map))
		return (false);
	// - check_floodfill
	// - check_map object: player, characters
	return (true);
}

bool	is_bordered(char **map)
{
	int	i;
	int	len;
	
	// first line 11111111111111 1111111 1111111111
	i = 0;
	if (map && map[0])
	{
		while (map[0] && map[0][i])
		{
			if (!(ft_isspace(map[0][i]) || map[0][i] == '1'))
				return (false);
			i++;
		}
	}
	// middle  1xxxxxxxxxx xxxx xxx1\n
	i = 0;
	while (map && map[++i])
	{
		len = ft_strlen(map[i]);
		// if (map[i][0] != '1' || map[i][len - 2] != '1')
		// 	return (false);
	}
	// last line 11111111 11111 111111111
	len = 0;
	while (map[i] && map[i][len])
	{
		if(!(ft_isspace(map[i][len]) || map[i][len] == '1'))
				return (false);
		len ++;
	}
	return (true);
}

