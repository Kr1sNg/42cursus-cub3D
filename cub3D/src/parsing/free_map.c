/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:40:45 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/19 09:01:24 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map_data(t_map *tmap)
{
	if (!tmap)
		return ;
	if (tmap && tmap->the_map)
		free_arr(&tmap->the_map);
	if (tmap && tmap->map_copy)
		free_arr(&tmap->the_map);
	if (tmap && tmap->path_e)
		free(tmap->path_e);
	if (tmap && tmap->path_n)
		free(tmap->path_n);
	if (tmap && tmap->path_s)
		free(tmap->path_s);
	if (tmap && tmap->path_w)
		free(tmap->path_w);
	free(tmap);
}
