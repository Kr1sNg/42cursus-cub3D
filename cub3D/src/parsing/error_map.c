/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:47:49 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/16 11:24:40 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	perror_and_exit(t_scene *scene, char *str)
{
	if (str)
		printf("Error!\n%s\n", str);
	if (scene)
		close_cube3d(scene);
}
