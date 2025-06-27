/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:43:22 by layang            #+#    #+#             */
/*   Updated: 2025/06/27 13:51:17 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	no_wall(t_scene	*scene, t_raycastor	*cast, int	*depth)
{
	if (!inside_map_array(cast->in_map.x, cast->in_map.y, scene))
		(*depth) = cast->dof;
	else
	{
		cast->rx += cast->stepx;
		cast->ry += cast->stepy;
		(*depth)++;
	}
}

int	hit_wall(t_map	*tmap, t_point	p, int is_3d)
{
	char	c;

	(void)is_3d;
	c = tmap->the_map[p.y][p.x];
	if (c == '0' || c == 'E' || c == 'W' || c == 'N' || c == 'S')
		return (0);
	else if (c == '1' || c == '2')
		return (1);
	else
		return (2);
}

/* int	hit_wall(t_map	*tmap, t_point	p, int is_3d)
{
	char	c;
	int		sp;

	c = tmap->the_map[p.y][p.x];
	sp = tmap->sprite_on;
	if (c == '0' || c == 'E' || c == 'W' || c == 'N' || c == 'S'
		|| (is_3d && c == '3' && sp == 0))
		return (0);
	else if (c == '1' || c == '2')
		return (1);
	else
		return (2);
} */

void	renew_pos_in_map(t_scene	*scene, t_raycastor	*cast)
{
	int	px;
	int	py;

	px = scene->tmap->player->posx;
	py = scene->tmap->player->posy;
	cast->in_map.x = px + floor(cast->rx / cast->grid) - 5;
	cast->in_map.y = py + floor(cast->ry / cast->grid) - 5;
}

static t_hit	nonvertical_side_wall(t_raycastor	*cast)
{
	if (cast->ra == 0.0)
		return (EAST);
	else if (cast->ra == M_PI)
		return (WEST);
	else if (cast->ra > M_PI)
		return (SOUTH);
	else
		return (NORTH);
}

t_hit	find_hit_side(t_raycastor	*cast, char c, int is_dir, int is_v)
{
	if (c == '1' || is_dir == 1)
	{
		if (is_v)
		{
			if (cast->ra == M_PI / 2)
				return (NORTH);
			else if (cast->ra == 3 * M_PI / 2)
				return (SOUTH);
			else if ((cast->ra > M_PI / 2) && (cast->ra < 3 * M_PI / 2))
				return (WEST);
			else
				return (EAST);
		}
		else
			return (nonvertical_side_wall(cast));
	}
	else if (c == '2')
		return (DOOR);
	else if (c == '3')
		return (SPRITE);
	else
		return (DEFAULT);
}
