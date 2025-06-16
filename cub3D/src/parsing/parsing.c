/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/16 11:51:18 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_parsing(char *path, t_scene *scene)
{
	char	**lines;
	int		i;

	lines = NULL;
	scene->tmap = ft_calloc(1, sizeof(t_map));
	if (!scene->tmap)
		return (printf("Malloc failed\n"), -42);

	if (!is_cub_file(path))
		return (printf("Invalid .cub file\n"), -42);

	lines = read_file(path);
	if (!lines)
		return (printf("Cannot open or Empty file\n"), -42);

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
