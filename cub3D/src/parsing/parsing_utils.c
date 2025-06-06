/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:56:18 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/06 18:44:47 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// for textures line

// NO ./path_to_the_north_texture

void	parse_texture_line(char *line, t_map *map)
{	
	char **split;

	printf("line: %s\n", line);
	split = ft_split_charset(line, " 	\n");
	if (!split || !split[0] || !split[1])
		return (ft_split_free(split), print_error("split"), exit(EXIT_FAILURE));
	if (is_texture_line(line) == 1)
	{
		if (map->count.no_line)
			return (ft_split_free(split), print_error("Duplicate texture line"), exit(EXIT_FAILURE));
		map->count.no_line = 1;
		map->tex_n = ft_strdup(split[1]);
	}
	else if (is_texture_line(line) == 2)
	{
		if (map->count.so_line)
			return (ft_split_free(split), print_error("Duplicate texture line"), exit(EXIT_FAILURE));
		map->count.so_line = 1;
		map->tex_s = ft_strdup(split[1]);
	}
	else if (is_texture_line(line) == 3)
	{
		if (map->count.we_line)
			return (ft_split_free(split), print_error("Duplicate texture line"), exit(EXIT_FAILURE));
		map->count.we_line = 1;
		map->tex_w = ft_strdup(split[1]);
	}
	else if (is_texture_line(line) == 4)
	{
		if (map->count.ea_line)
			return (ft_split_free(split), print_error("Duplicate texture line"), exit(EXIT_FAILURE));
		map->count.ea_line = 1;
		map->tex_e = ft_strdup(split[1]);
	}
	ft_split_free(split);
}

void	parse_color_line(char *line, t_map *map)
{
	char **split;

	printf("color: %s\n", line);
	split = ft_split_charset(line, " ,	\n");
	if (!split || !split[0] || !split[1] || !split[2] || !split[3])
		return (ft_split_free(split), print_error("split color"), exit(EXIT_FAILURE));
	if (is_color_line(line) == 5)
	{
		if (map->count.c_line)
			return (ft_split_free(split), print_error("Duplicate color line"), exit(EXIT_FAILURE));
		map->count.c_line = 1;
		printf("rgb collor in char1: %s, %s, %s\n", split[1], split[2], split[3]);
		map->color_c = color_int(split[1], split[2], split[3]);
	}
	else if (is_color_line(line) == 6)
	{
		if (map->count.f_line)
			return (ft_split_free(split), print_error("Duplicate color line"), exit(EXIT_FAILURE));
		map->count.f_line = 1;
		printf("rgb collor in char1: %s, %s, %s\n", split[1], split[2], split[3]);
		map->color_f = color_int(split[1], split[2], split[3]);
	}
	ft_split_free(split);
}

int	color_int(char *r, char *g, char *b)
{
	int	value;
	int	ri;
	int	gi;
	int	bi;
	
	if (!r || !g || !b)
		return (-42);
	ri = ft_atoi(r);
	gi = ft_atoi(g);
	bi = ft_atoi(b);
	printf("rgb collor in int: %i, %i, %i\n", ri, gi, bi);
	if ((0 > ri || ri > 255) || (0 > gi || gi > 255) || (0 > bi || bi > 255))
		return (-42);
	value = ((ri << 16) | (gi << 8) | bi);
	return (value);
}


