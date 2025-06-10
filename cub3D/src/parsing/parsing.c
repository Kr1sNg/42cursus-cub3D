/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/10 14:24:39 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/*
Parsing:
	- check file ".cub"
	- open file
	- read file into char **lines
	- read lines by line then
		- if it's texture => input in texture + count in texture count
		- if it's color => input in color + count in count color
		- if it's map => input into maps	
*/

static int	check_file_and_read_lines(char *path, t_map *map, char ***lines)
{
	if (!is_cub_file(path))
		return (perror_and_exit(map, "Invalid .cub file"), -42);
	*lines = read_file(path);
	if (!*lines)
		return (perror_and_exit(map, "Cannot open or Empty file"), -42);
	return (0);
}

static int	parse_non_map_lines(t_map *map, char **lines, int i)
{
	while (lines[i] && !is_map_line(lines[i]))
	{
		if (is_texture_line(lines[i]))
			parse_texture_line(map, lines, i);
		else if (is_color_line(lines[i]))
			parse_color_line(map, lines, i);
		else if (!is_empty_line(lines[i]) && !is_map_line(lines[i]))
		{
			printf("error line: %s\n", lines[i]);
			ft_split_free(lines);
			return (perror_and_exit(map, "Invalid line before map block"), -42);
		}
		i++;
	}
	if (!map->count.c_line || !map->count.f_line || !map->count.ea_line
		|| !map->count.no_line || !map->count.so_line || !map->count.we_line)
		return (ft_split_free(lines),
			perror_and_exit(map, "Missing element"), -42);
	return (i);
}

static int	parse_map_if_present(t_map *map, char **lines, int i)
{
	int	status;

	status = 0;
	if (lines && lines[i] && is_map_line(lines[i]))
	{
		status = parse_map_block(map, &lines[i]);
		while (lines[i] && is_map_line(lines[i]))
			i++;
	}
	if (status < 0)
		i = -42;
	return (i);
}

static int	check_nothing_after_map(char **lines, int i, t_map *map)
{
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			ft_split_free(lines);
			return (perror_and_exit(map, "map is not in the last of file"), -42);
		}
		i++;
	}
	return (0);
}

int	ft_parsing(char *path, t_map *map)
{
	char	**lines;
	int		i;

	lines = NULL;
	ft_memset(map, 0, sizeof(t_map));
	i = check_file_and_read_lines(path, map, &lines);
	if (i < 0)
		return (ft_split_free(lines), -42);
	i = parse_non_map_lines(map, lines, i);
	if (i < 0)
		return (ft_split_free(lines), -42);
	i = parse_map_if_present(map, lines, i);
	if (i < 0)
		return (ft_split_free(lines), perror_and_exit(map, "Invalid Block"), -42);
	if (check_nothing_after_map(lines, i, map) < 0)
		return (ft_split_free(lines), perror_and_exit(map, "Unexpected line after map"), -42);
	
	if (!is_valid_map(map, lines))
		return (ft_split_free(lines), perror_and_exit(map, "Invalid Map"), -42);
	
	printf("after parsing: s link [%s]\n", (char *)map->tex_s);
	printf("after parsing: e link [%s]\n", (char *)map->tex_e);
	printf("after parsing: n link [%s]\n", (char *)map->tex_n);
	printf("after parsing: w link [%s]\n", (char *)map->tex_w);
	printf("after parsing: c color [%i]\n", map->color_c);
	printf("after parsing: f color [%i]\n", map->color_f);
	print_map(map);
	printf("num of player: %i\n", map->count.player_count);
	printf("playser posx %i, posy %i\n", map->posx, map->posy);
	
	ft_split_free(lines);
	return (0);
}

// int	ft_parsing(char *path, t_map *map)
// {
// 	char **lines;
// 	int		i;
	
// 	i = 0;
// 	if (!is_cub_file(path))
// 		return(perror_and_exit(map, "Invalid .cub file"), -42);
// 	lines = read_file(path);
// 	if (!lines)
// 		return(perror_and_exit(map, "Cannot open or Empty file"), -42);
// 	while (lines[i] && !is_map_line(lines[i]))
// 	{
// 		if (is_texture_line(lines[i]))
// 			parse_texture_line(map, lines[i]);
// 		else if (is_color_line(lines[i]))
// 			parse_color_line(map, lines[i]);
// 		else if (!is_empty_line(lines[i]))
// 		{
// 			ft_split_free(lines);
// 			return(perror_and_exit(map, "Invalid line before map block"), -42);
// 		}
// 		i++;
// 	}
// 	if (lines[i] && is_map_line(lines[i]))
// 	{
// 		parse_map_block(&lines[i], map);
// 		i++;
// 	}
// 	while (lines[i] && is_map_line(lines[i]))
// 		i++;
// 	if (lines[i])
// 	{
// 		ft_split_free(lines);
// 		return(perror_and_exit(map, "map is not in the last of file"), -42);
// 	}
	// printf("after parsing: s link [%s]\n", (char *)map->tex_s);
	// printf("after parsing: e link [%s]\n", (char *)map->tex_e);
	// printf("after parsing: n link [%s]\n", (char *)map->tex_n);
	// printf("after parsing: w link [%s]\n", (char *)map->tex_w);
	// printf("after parsing: c color [%i]\n", map->color_c);
	// printf("after parsing: f color [%i]\n", map->color_f);
	// print_map(map);
	// printf("num of player: %i\n", map->count.player_count);
	// printf("playser posx %i, posy %i\n", map->posx, map->posy);
// 	ft_split_free(lines);
// 	return (0);
