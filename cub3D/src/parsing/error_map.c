/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:47:49 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/08 22:53:28 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	perror_and_exit(t_map *map, char *str)
{
	if (map)
		free_map_data(map);
	if (str)
		printf("Error!\n%s\n", str);
	exit(EXIT_FAILURE);
}
