/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 10:01:15 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_texture_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "NO ", 3))
		return (1);
	else if (!ft_strncmp(&line[i], "SO ", 3))
		return (2);
	else if (!ft_strncmp(&line[i], "WE ", 3))
		return (3);
	else if (!ft_strncmp(&line[i], "EA ", 3))
		return (4);
	return (0);
}

int	is_color_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(&line[i], "C ", 2))
		return (5);
	else if (!ft_strncmp(&line[i], "F ", 2))
		return (6);
	return (0);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_map_obj(char c)
{
	if (c == ' ' || c == '	' || c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == '\n')
		return (true);
	return (false);
}

bool	is_map_line(char *s)
{
	int	i;

	if (is_empty_line(s))
		return (false);
	i = 0;
	while (s[i])
	{
		if (!is_map_obj(s[i]))
			return (false);
		i++;
	}
	return (true);
}
