/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/04 19:31:03 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/*
Parsing:
	- check file ".cub"
	- check open file
	- check read file
	
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
	
	if (!is_cub_file(path))
		exit(print_error("Invalid .cub file"));
	
	lines = read_file(path);
	
}

int	is_texture(char *line)
{
	if 
}

bool	is_texture_line(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strncmp(&line[i], "NO ", 3))
		return 
	
}


bool	is_color_line(char *line);

