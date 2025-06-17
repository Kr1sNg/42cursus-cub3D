/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/17 11:29:54 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	check_file_and_read(char *path, char ***lines)
{
	if (!is_cub_file(path))
		return (print_err("Invalid .cub file"), false);
	*lines = read_file(path);
	if (!*lines)
		return (print_err("Cannot open or Empty file"), false);
	return (true);
}

bool	parse_headers(t_map *map, char **lines, int *i)
{
	*i = 0;
	while (lines[*i] && !is_map_line(lines[*i]))
	{
		if (is_texture_line(lines[*i]))
		{
			if (!parse_texture_line(map, lines, *i))
				return (false);
		}
		else if (is_color_line(lines[*i]))
		{
			if (!parse_color_line(map, lines, *i))
				return (false);
		}
		else if (!is_empty_line(lines[*i]))
			return (print_err("Invalid line before map block\n"), false);
		(*i)++;
	}
	if (!lines[*i])
		return (print_err("No map block found\n"), false);
	return (true);
}

static bool	parse_and_validate_map(t_map *map, char **lines, int i)
{
	if (!parse_map_block(map, &lines[i]))
		return (print_err("Map block invalid\n"), false);
	while (lines[i] && is_map_line(lines[i]))
		i++;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
			return (print_err("Map must be at the end\n"), false);
		i++;
	}
	if (!is_valid_map(map, lines))
		return (false);
	return (true);
}


int	ft_parsing(char *path, t_scene *scene)
{
	char	**lines;
	int		i;

	lines = NULL;
	scene->tmap = ft_calloc(1, sizeof(t_map));
	if (!scene->tmap)
		return (print_err("Malloc failed"), -42);
	
	if (!check_file_and_read(path, &lines))
		return (-42);
	
	if (!parse_headers(scene->tmap, lines, &i))
		return (ft_split_free(lines), -42);
	
	if (!parse_and_validate_map(scene->tmap, lines, i))
		return (ft_split_free(lines), -42);
	ft_split_free(lines);
	return (0);
}




/*
int	ft_parsing(char *path, t_scene *scene)
{
	char	**lines;
	int		i;

	lines = NULL;
	scene->tmap = ft_calloc(1, sizeof(t_map));
	if (!scene->tmap)
		return (print_err("Malloc failed"), -42);

	if (!is_cub_file(path))
		return (print_err("Invalid .cub file"), -42);

	lines = read_file(path);
	if (!lines)
		return (print_err("Cannot open or Empty file"), -42);

	i = 0;
	while (lines[i] && !is_map_line(lines[i]))
	{
		if (is_texture_line(lines[i]))
		{
			if (!parse_texture_line(scene->tmap, lines, i))
				return (ft_split_free(lines), -42);
		}		
		else if (is_color_line(lines[i]))
		{
			if (!parse_color_line(scene->tmap, lines, i))
				return (ft_split_free(lines), -42);
		}		
		else if (!is_empty_line(lines[i]))
			return (ft_split_free(lines),
				printf("Invalid line before map block\n"), -42);
		i++;
	}
	if (!lines[i])
		return (ft_split_free(lines), printf("No map block found\n"), -42);

	if (!parse_map_block(scene->tmap, &lines[i]))
		return (ft_split_free(lines), printf("No map block found 2\n"), -42);
	while (lines[i] && is_map_line(lines[i]))
		i++;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
			return (ft_split_free(lines), printf("Map must be at the end\n"), -42);
		i++;
	}
	if (!is_valid_map(scene->tmap, lines))
		return (ft_split_free(lines), -42);
	ft_split_free(lines);
	return (0);
}
*/