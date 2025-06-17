/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:56:18 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/17 11:03:42 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	parse_color_line(t_map *tmap, char **lines, int i)
{
	char	**split;
	int		color;

	split = ft_split_charset(lines[i], " ,	\n");
	if (!split || !split[0] || !split[1] || !split[2] || !split[3]
		|| (split && ft_tablen(split) > 4))
		return (ft_split_free(split), print_err("Invalid color"), false);
	color = color_toi(split);
	if (color < 0)
		return (ft_split_free(split), print_err("Invalid color"), false);
	if (is_color_line(lines[i]) == 5)
	{
		if (tmap->count.c_line)
			return (ft_split_free(split), print_err("Dup color"), false);
		tmap->count.c_line = 1;
		tmap->color_c = color;
	}
	else if (is_color_line(lines[i]) == 6)
	{
		if (tmap->count.f_line)
			return (ft_split_free(split), print_err("Dup color"), false);
		tmap->count.f_line = 1;
		tmap->color_f = color;
	}
	return (ft_split_free(split), true);
}

static bool	store_texture(t_map *map, char **split, char *line)
{
	int	type;
	
	type = is_texture_line(line);
	if (type == 1 && !map->count.no_line)
		return (map->count.no_line = 1, 
			map->path_n = ft_strdup(split[1]), true);
	if (type == 2 && !map->count.so_line)
		return (map->count.so_line = 1,
			map->path_s = ft_strdup(split[1]), true);
	if (type == 3 && !map->count.we_line)
		return (map->count.we_line = 1,
			map->path_w = ft_strdup(split[1]), true);
	if (type == 4 && !map->count.ea_line)
		return (map->count.ea_line = 1,
			map->path_e = ft_strdup(split[1]), true);
	if (type >= 1 && type <= 4)
		return (print_err("Duplicate texture"), false);
	return (print_err("Unknown texture type"), false);
}



bool	parse_texture_line(t_map *map, char **lines, int i)
{	
	char **split;
	
	if (!lines || !(*lines))
		return (print_err("Missing line"), false);
	split = ft_split_charset(lines[i], " \n");
	if (!split || !split[0] || !split[1] || (split && ft_tablen(split) > 2))
		return (ft_split_free(split), print_err("Invalid texture"), false);
	if (!store_texture(map, split, lines[i]))
		return (ft_split_free(split), false);
	ft_split_free(split);
	return (true);
}




	/*	if (is_texture_line(lines[i]) == 1)
	{
		if (map->count.no_line)
			return (ft_split_free(split), printf("Dup texture\n"), false);
		map->count.no_line = 1;
		map->path_n = ft_strdup(split[1]);
	}
	else if (is_texture_line(lines[i]) == 2)
	{
		if (map->count.so_line)
			return (ft_split_free(split), printf("Dup texture\n"), false);
		map->count.so_line = 1;
		map->path_s = ft_strdup(split[1]);
	}
	else if (is_texture_line(lines[i]) == 3)
	{
		if (map->count.we_line)
			return (ft_split_free(split), printf("Dup texture\n"), false);
		map->count.we_line = 1;
		map->path_w = ft_strdup(split[1]);
	}
	else if (is_texture_line(lines[i]) == 4)
	{
		if (map->count.ea_line)
			return (ft_split_free(split), printf("Dup texture\n"), false);
		map->count.ea_line = 1;
		map->path_e = ft_strdup(split[1]);
	}
	else
		return (ft_split_free(split), printf("Unvalid texture\n"), false);
	ft_split_free(split);
	return (true);
}
	*/

