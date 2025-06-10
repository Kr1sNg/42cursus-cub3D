/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:56:18 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/10 18:42:03 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_texture(char **dst, int *count_line, char **split, t_map *map)
{
	if (*count_line)
	{
		perror_and_exit(map, "Duplicate texture");
		return ;
	}
	*count_line = 1;
	*dst = ft_strdup(split[1]);
	if (!*dst)
		perror_and_exit(map, "Texture strdup failed");
}

static void	parse_texture_dispatch(t_map *map, char **split, char *line,
	char **lines)
{
	int	type;

	type = is_texture_line(line);
	if (type == 1)
		set_texture(&map->path_n, &map->count.no_line, split, map);
	else if (type == 2)
		set_texture(&map->path_s, &map->count.so_line, split, map);
	else if (type == 3)
		set_texture(&map->path_w, &map->count.we_line, split, map);
	else if (type == 4)
	{
		set_texture(&map->path_e, &map->count.ea_line, split, map);
		printf("path_e: %s\n", map->path_e);
	}
	else
	{
		ft_split_free(lines);
		ft_split_free(split);
		perror_and_exit(map, "Unknown texture identifier");
	}
}

void	parse_texture_line(t_map *map, char **lines, int i)
{
	char	**split;

	split = ft_split_charset(lines[i], " \n");
	if (!split || !split[0] || !split[1] || ft_tablen(split) > 2)
	{
		ft_split_free(lines);
		ft_split_free(split);
		perror_and_exit(map, "Invalid texture");
	}
	printf("texture after split: %s\n", split[1]);
	parse_texture_dispatch(map, split, lines[i], lines);
	printf("after dispatch e: %s\n", map->path_e);
	ft_split_free(split);
}

void	parse_color_line(t_map *map, char **lines, int i)
{
	char	**split;

	split = ft_split_charset(lines[i], " ,	\n");
	if (!split || !split[0] || !split[1] || !split[2] || !split[3]
		|| (split && ft_tablen(split) > 4))
		return (ft_split_free(lines), ft_split_free(split),
			perror_and_exit(map, "Invalid color"));
	if (is_color_line(lines[i]) == 5)
	{
		if (map->count.c_line)
			return (ft_split_free(lines), ft_split_free(split),
				perror_and_exit(map, "Dup color"));
		map->count.c_line = 1;
		map->color_c = color_toi(map, split, lines);
	}
	else if (is_color_line(lines[i]) == 6)
	{
		if (map->count.f_line)
			return (ft_split_free(lines), ft_split_free(split),
				perror_and_exit(map, "Dup color"));
		map->count.f_line = 1;
		map->color_f = color_toi(map, split, lines);
	}
	ft_split_free(split);
}

/*
void	parse_texture_line(t_map *map, char **lines, int i)
{	
	char **split;
	if (lines && lines[i])
		split = ft_split_charset(lines[i], " \n");
	if (!split || !split[0] || !split[1] || (split && ft_tablen(split) > 2))
		return (ft_split_free(lines), ft_split_free(split),
			perror_and_exit(map, "Invalid texture"));
	if (is_texture_line(lines[i]) == 1)
	{
		if (map->count.no_line)
			return (ft_split_free(lines), ft_split_free(split),
				perror_and_exit(map, "Dup texture"));
		map->count.no_line = 1;
		map->path_n = ft_strdup(split[1]);
	}
	else if (is_texture_line(lines[i]) == 2)
	{
		if (map->count.so_line)
			return (ft_split_free(lines), ft_split_free(split),
				perror_and_exit(map, "Dup texture"));
		map->count.so_line = 1;
		map->path_s = ft_strdup(split[1]);
	}
	else if (is_texture_line(lines[i]) == 3)
	{
		if (map->count.we_line)
			return (ft_split_free(lines), ft_split_free(split),
				perror_and_exit(map, "Dup texture"));
		map->count.we_line = 1;
		map->path_w = ft_strdup(split[1]);
	}
	else if (is_texture_line(lines[i]) == 4)
	{
		if (map->count.ea_line)
			return (ft_split_free(lines), ft_split_free(split),
				perror_and_exit(map, "Dup texture"));
		map->count.ea_line = 1;
		map->path_e = ft_strdup(split[1]);
	}
	ft_split_free(split);
}
*/
