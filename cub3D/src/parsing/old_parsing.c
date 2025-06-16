// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parsing.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
// /*   Updated: 2025/06/16 10:02:37 by tat-nguy         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/cub3d.h"
// /*
// Parsing:
// 	- check file ".cub"
// 	- open file
// 	- read file into char **lines
// 	- read lines by line then
// 		- if it's texture => input in texture + count in texture count
// 		- if it's color => input in color + count in count color
// 		- if it's map => input into maps	
// */

// static int	check_file_and_read_lines(char *path, char ***lines)
// {
// 	if (!is_cub_file(path))
// 		return (printf("Invalid .cub file"), -42);
// 	*lines = read_file(path);
// 	if (!*lines)
// 		return (printf("Cannot open or Empty file"), -42);
// 	return (0);
// }

// static int	parse_non_map_lines(t_scene *scene, char **lines, int i)
// {
// 	while (lines[i] && !is_map_line(lines[i]))
// 	{
// 		if (is_texture_line(lines[i]))
// 		{
// 			if (!(parse_texture_line(scene, lines, i)))
// 				return (-42);
// 		}
// 		else if (is_color_line(lines[i]))
// 			parse_color_line(scene, lines, i);
// 		else if (!is_empty_line(lines[i]) && !is_map_line(lines[i]))
// 			return (ft_split_free(lines), perror_and_exit(scene, "Invalid line before map block"), -42);
// 		i++;
// 	}
// 	if (!scene->tmap->count.c_line || !scene->tmap->count.f_line || !scene->tmap->count.ea_line
// 		|| !scene->tmap->count.no_line || !scene->tmap->count.so_line || !scene->tmap->count.we_line)
// 		return (ft_split_free(lines),
// 			perror_and_exit(scene, "Missing element"), -42);
// 	return (i);
// }

// static int	parse_map_if_present(t_scene *scene, char **lines, int i)
// {
// 	int	status;

// 	status = 0;
// 	if (lines && lines[i] && is_map_line(lines[i]))
// 	{
// 		status = parse_map_block(scene->tmap, &lines[i]);
// 		while (lines[i] && is_map_line(lines[i]))
// 			i++;
// 	}
// 	if (status < 0)
// 		i = -42;
// 	return (i);
// }

// static int	check_nothing_after_map(char **lines, int i, t_scene *scene)
// {
// 	while (lines[i])
// 	{
// 		if (!is_empty_line(lines[i]))
// 		{
// 			ft_split_free(lines);
// 			return (perror_and_exit(scene, "map is not in the last of file"), -42);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_parsing(char *path, t_scene *scene)
// {
// 	char	**lines;
// 	int		i;

// 	lines = NULL;
// 	scene->tmap = ft_calloc(1, sizeof(t_map));
// 	if (!scene->tmap)
// 		return (printf("Malloc failed"), -42);
		
// 	i = check_file_and_read_lines(path, &lines);
// 	if (i < 0)
// 		return (ft_split_free(lines), -42); //OK!
		
// 	i = parse_non_map_lines(scene, lines, i);
// 	if (i < 0)
// 		return (ft_split_free(lines), -42);
// 	i = parse_map_if_present(scene, lines, i);
// 	if (i < 0)
// 		return (ft_split_free(lines), perror_and_exit(scene, "Invalid Block"), -42);
// 	if (check_nothing_after_map(lines, i, scene) < 0)
// 		return (ft_split_free(lines), perror_and_exit(scene, "Unexpected line after map"), -42);
	
// 	if (!is_valid_map(scene, lines))
// 		return (ft_split_free(lines), perror_and_exit(scene, "Invalid Map"), -42);
	
// 	ft_split_free(lines);
// 	return (0);
// }

// // int	ft_parsing(char *path, t_map *map)
// // {
// // 	char **lines;
// // 	int		i;
	
// // 	i = 0;
// // 	if (!is_cub_file(path))
// // 		return(perror_and_exit(map, "Invalid .cub file"), -42);
// // 	lines = read_file(path);
// // 	if (!lines)
// // 		return(perror_and_exit(map, "Cannot open or Empty file"), -42);
// // 	while (lines[i] && !is_map_line(lines[i]))
// // 	{
// // 		if (is_texture_line(lines[i]))
// // 			parse_texture_line(map, lines[i]);
// // 		else if (is_color_line(lines[i]))
// // 			parse_color_line(map, lines[i]);
// // 		else if (!is_empty_line(lines[i]))
// // 		{
// // 			ft_split_free(lines);
// // 			return(perror_and_exit(map, "Invalid line before map block"), -42);
// // 		}
// // 		i++;
// // 	}
// // 	if (lines[i] && is_map_line(lines[i]))
// // 	{
// // 		parse_map_block(&lines[i], map);
// // 		i++;
// // 	}
// // 	while (lines[i] && is_map_line(lines[i]))
// // 		i++;
// // 	if (lines[i])
// // 	{
// // 		ft_split_free(lines);
// // 		return(perror_and_exit(map, "map is not in the last of file"), -42);
// // 	}
// 	// printf("after parsing: s link [%s]\n", (char *)map->path_s);
// 	// printf("after parsing: e link [%s]\n", (char *)map->path_e);
// 	// printf("after parsing: n link [%s]\n", (char *)map->path_n);
// 	// printf("after parsing: w link [%s]\n", (char *)map->path_w);
// 	// printf("after parsing: c color [%i]\n", map->color_c);
// 	// printf("after parsing: f color [%i]\n", map->color_f);
// 	// print_map(map);
// 	// printf("num of player: %i\n", map->count.player_count);
// 	// printf("playser posx %i, posy %i\n", map->posx, map->posy);
// // 	ft_split_free(lines);
// // 	return (0);
