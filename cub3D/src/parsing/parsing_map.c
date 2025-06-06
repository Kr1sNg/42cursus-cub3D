/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:23:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/06 20:30:54 by tat-nguy         ###   ########.fr       */
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

void	parse_map_lines(char **line, t_map *map)
{
	int	height;
	int	width;
	int	i;
	int	len;

	i = 0;
	width = 0;
	height = 0;
	
	while (line[i])
	{
		if (!is_map_line(line[i]))
			exit(print_error("empty line in map"));
		len = ft_strlen(line[i]);
		if (len > width)
			width = len;
		i++;
	}
	height = i;
	map->the_map = ft_calloc(height + 1, sizeof(char *));
	if (!map->the_map)
		exit(print_error("Malloc failed"));
	i = -1;
	while (++i < height)
		map->the_map[i] = ft_strdup(line[i]);
	
}

void	print_map(t_map *map)
{
	int	i;
	
	if (!map->the_map)
		printf("There's no map\n");
	i = -1;
	while (map->the_map[++i])
		printf("map[%i]: [%s]\n", i, map->the_map[i]);
}

int	is_valid_map(char **map)
{
	- check_border( - line 0 + line n has all 1, all others line start and end with 1)
	- check_floodfill
	- check_map object: player, characters
}

bool	is_bordered()