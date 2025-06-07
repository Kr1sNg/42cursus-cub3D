/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/07 09:04:51 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



int	main(int ac, char **av)
{
	t_map	map;
	
	ft_memset(&map, 0, sizeof(t_map));
	
	if (ac != 2)
		return (print_error("Usage: ./cub3d valid_map.cub"));

	
	ft_parsing(av[1], &map);

	free_map_data(&map);
	
	printf("MAIN OK!\n");	
	return (0);
}

void	free_map_data(t_map *map)
{
	if (!map)
		return ;
	if (map->the_map)
		ft_split_free(map->the_map);
	if (map->tex_e)
		free(map->tex_e);
	if (map->tex_n)
		free(map->tex_n);
	if (map->tex_s)
		free(map->tex_s);
	if (map->tex_w)
		free(map->tex_w);
}