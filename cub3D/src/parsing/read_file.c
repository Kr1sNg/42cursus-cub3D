/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:19:45 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 10:36:28 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	char	*line;
	char	**lines;
	int		count;

	count = 0;
	lines = ft_calloc(MAX_LINES, sizeof(char *));
	if (!lines)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines[count++] = line;
	}
	lines[count++] = NULL;
	close(fd);
	return (lines);
}
