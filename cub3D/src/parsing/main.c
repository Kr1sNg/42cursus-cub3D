/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/06 15:17:14 by tat-nguy         ###   ########.fr       */
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

	free(map.tex_e);
	free(map.tex_n);
	free(map.tex_s);
	free(map.tex_w);
	printf("MAIN OK!\n");	
	return (0);
}

