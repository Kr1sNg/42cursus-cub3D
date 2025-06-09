/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:40:45 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/09 10:23:13 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
