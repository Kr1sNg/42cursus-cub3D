/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/10 15:34:00 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;
	
	if (ac != 2)
		return (printf("Usage: ./cub3d valid_map.cub"));
	
	ft_parsing(av[1], &map);
	
	
	free_map_data(&map);
	return (0);
}

