/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/05 22:38:34 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/*
Parsing:
	- check file ".cub"
	- check open file
	- read file into char **lines
	- read lines by line then 
		- if it's texture => input in texture
		- if it's color => input in color
	
*/

bool	is_cub_file(char *path)
{
	size_t	len;
	char	*ext;

	ext = ".cub";
	len = ft_strlen(path);
	if (len < 4)
		return (false);
	return (!ft_strcmp(&path[len - 4], ext));
}

char	**read_file(char *path)
{
	int		fd;
	char 	*line;
	char 	**lines;
	int		count;

	count = 0;
	lines = ft_calloc(MAX_LINES, sizeof(char *));
	if (!lines)
		exit(print_error("Cannot allocate memory"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(print_error("Cannot open file"));
	while ((line = get_next_line(fd)))
		lines[count++] = line;
	lines[count++] = NULL;
	close(fd);
	return (lines);
}

int	ft_parsing(char *path, t_map *map)
{
	char **lines;
	int		i;
	
	i = 0;
	if (!is_cub_file(path))
		exit(print_error("Invalid .cub file"));
	
	lines = read_file(path);
	if (!lines)
		exit(print_error("Empty file!"));
	while (lines[i] && !is_map_line(lines[i]))
	{
		if (is_texture_line(lines[i]))
			parse_texture_line(lines[i], map);
		else if (is_color_line(lines[i]))
			parse_color_line(lines[i], map);
		else if (is_empty_line(lines[i]))
			printf("empty line\n");
		else
		{
			free(lines);	
			exit(print_error("Invalid line before map"));
		}
		i++;
	}
	// check map
	while (lines[i] && is_map_line(lines[i]))
	{
		printf("Map[%i]: %s\n", i, lines[i]);
		i++;
	}
	if (lines[i])
	{
		free(lines);
		exit(print_error("map is not in the last of file"));
	}
	printf("File OK!");
	free(lines);
	return (0);
}

int	parse_texture_line(char *line, t_map *map)
{
	// t_texture	*texture;
	
	// texture = ft_calloc(1, sizeof(texture));
	// if (!texture)
	// 	exit(print_error("Cannot allocate memory"));
	
	(void)map;
	
	if (line)
		printf("Texture: %s\n", line);
	return (1);
}

int	parse_color_line(char *line, t_map *map)
{
	(void)map;
	if (line)
		printf("Color: %s\n", line);
	return (1);
}

bool	is_texture_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "NO ", 3))
		return (true);
	else if (!ft_strncmp(&line[i], "SO ", 3))
		return (true);
	else if (!ft_strncmp(&line[i], "WE ", 3))
		return (true);
	else if (!ft_strncmp(&line[i], "EA ", 3))
		return (true);
	return (false);
}

bool	is_color_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "F ", 2))
		return (true);
	else if (!ft_strncmp(&line[i], "C ", 2))
		return (true);
	return (false);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
	}
	if (line[i])
		return (false);
	return (true);
}

bool	is_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] && (s[i] == '1'))// || s[i] == '0' || s[i] == 'N'
			//|| s[i] == 'S' || s[i] == 'E' || s[i] == 'W'))
		return (true);
	return (false);
}

int	print_error(char *str)
{
	write(2, "Error\n", 6);
	while (*str)
		write(2, str++, 1);
	write(2, "\n", 1);
	return (1);
}