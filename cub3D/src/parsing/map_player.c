/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:23:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 10:31:28 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	set_player(t_map *map, char dir, int x, int y)
{
	if (map->count.player_count != 0)
		return (false);
	map->count.player_count = dir;
	map->posx = x;
	map->posy = y;
	if (dir == 'N' || dir == 'S')
	{
		map->dirx = 0;
		if (dir == 'N')
			map->diry = -1;
		map->diry = 1;
	}
	else if (dir == 'W' || dir == 'E')
	{
		map->diry = 0;
		if (dir == 'W')
			map->dirx = -1;
		map->dirx = 1;
	}
	return (true);
}

static bool	parse_player_line(t_map *map, char *line, int y)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (is_player_char(line[x]))
		{
			if (!set_player(map, line[x], x, y))
				return (false);
		}
		x++;
	}
	return (true);
}

bool	has_located_player(t_map *map)
{
	int	i;

	if (!map || !map->the_map)
		return (false);
	i = 0;
	while (map->the_map[i])
	{
		if (!parse_player_line(map, map->the_map[i], i))
			return (false);
		i++;
	}
	printf("PLAYER posx: %i, posy: %i\n", map->posx, map->posy);
	return (true);
}

/*
bool	has_located_player(t_map *map)
{
	int i;
	int	j;
	
	if (!map || !map->the_map)
		return (false);
	i = 0;
	while (map->the_map[i])
	{
		j = 0;
		while (map->the_map[i] && map->the_map[i][j])
		{
			if (map->the_map[i][j] == 'N')
			{
				if (map->count.player_count != 0)
					return (false);
				map->count.player_count = 'N';
				map->posx = j;
				map->posy = i;
				map->dirx = 0;
				map->diry = -1;
			}
			else if (map->the_map[i][j] == 'S')
			{
				if (map->count.player_count != 0)
					return (false);
				map->count.player_count = 'S';
				map->posx = j;
				map->posy = i;
				map->dirx = 0;
				map->diry = 1;
			}
			else if (map->the_map[i][j] == 'W')
			{
				if (map->count.player_count != 0)
					return (false);
				map->count.player_count = 'W';
				map->posx = j;
				map->posy = i;
				map->dirx = -1;
				map->diry = 0;
			}
			else if (map->the_map[i][j] == 'E')
			{
				if (map->count.player_count != 0)
					return (false);
				map->count.player_count = 'E';
				map->posx = j;
				map->posy = i;
				map->dirx = 1;
				map->diry = 0;
			}
			j++;
		}
		i++;
	}
	printf("PLAYER posx: %i, posy: %i\n", map->posx, map->posy);
	return (true);
}
*/
