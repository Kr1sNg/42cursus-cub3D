/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:59:38 by layang            #+#    #+#             */
/*   Updated: 2025/06/25 20:05:42 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	near_wall(t_map	*tmap, double fx, double fy, t_point	p)
{
	int		check_x;
	int		check_y;
	int		grid;
	double	margin;

	grid = tmap->player->ray2->grid;
	margin = grid / 6.0;
	check_x = (int)((fx + p.x * margin) / grid);
	check_y = (int)((fy + p.y * margin) / grid);
	if (check_x < 0 || check_y < 0
		|| check_y >= tmap->count.map_lines
		|| check_x >= (int)ft_strlen(tmap->the_map[check_y]))
		return (1);
	if (tmap->the_map[check_y][check_x] != '0'
		&& tmap->the_map[check_y][check_x] != 'N'
		&& tmap->the_map[check_y][check_x] != 'S'
		&& tmap->the_map[check_y][check_x] != 'E'
		&& tmap->the_map[check_y][check_x] != 'W'
		&& tmap->the_map[check_y][check_x] != '2')
		return (1);
	return (0);
}

static int	not_near_wall(t_map *tmap, double fx, double fy)
{
	int		i;
	int		j;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			if (!(i == 0 && j == 0))
			{
				if (near_wall(tmap, fx, fy, (t_point){i, j, 0}))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static void	get_new_place(double	*fx, double	*fy, t_map	*tmap, t_point	p)
{
	int		grid2;

	grid2 = tmap->player->ray2->grid;
	*fx = tmap->player->posx * grid2 + grid2 / 2 + tmap->player->ray2->offx;
	*fy = tmap->player->posy * grid2 + grid2 / 2 + tmap->player->ray2->offy;
	if (p.y == 0)
	{
		*fx += cos(tmap->player->p_angle) * p.x;
		*fy += -sin(tmap->player->p_angle) * p.x;
	}
	else
	{
		*fx += sin(tmap->player->p_angle) * p.x;
		*fy += cos(tmap->player->p_angle) * p.x;
	}
}

//floating point coor
void	floating_coord(t_map	*tmap, int n_pix, int sign)
{
	double	fx;
	double	fy;
	int		grid2;
	char	c;
	t_point	new;

	grid2 = tmap->player->ray2->grid;
	get_new_place(&fx, &fy, tmap, (t_point){n_pix, sign, 0});
	new.x = (int)floor(fx / grid2);
	new.y = (int)floor(fy / grid2);
	if (new.x >= 0 && new.y >= 0 && new.x < tmap->count.map_width
		&& new.y < tmap->count.map_lines
		&& new.x < (int)ft_strlen(tmap->the_map[new.y]))
	{
		c = tmap->the_map[new.y][new.x];
		if (c && (c == '0' || c == 'N' || c == 'S'
				|| c == 'E' || c == 'W' || c == '2')
			&& not_near_wall(tmap, fx, fy))
		{
			tmap->player->posx = new.x;
			tmap->player->posy = new.y;
			tmap->player->ray2->offx = fx - new.x * grid2 - grid2 / 2;
			tmap->player->ray2->offy = fy - new.y * grid2 - grid2 / 2;
		}
	}
}
