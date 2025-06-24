/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:34:46 by marvin            #+#    #+#             */
/*   Updated: 2025/06/24 12:58:58 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void init_doors_values(t_map   *tmap, int height, int width)
{
    int	y;
    int	x;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            if (tmap->the_map[y][x] == '2')
            {
                tmap->door_state[y][x] = DOOR_CLOSED;
                tmap->door_timer[y][x] = 0.0;
            }
            else
            {
                tmap->door_state[y][x] = -1;
                tmap->door_timer[y][x] = 0.0;
            }
            x++;
        }
        y++;
    }
}

int    init_doors(t_map   *tmap)
{
	int	y;
    int height;
    int width;

    height = tmap->count.map_lines;
    width = tmap->count.map_width;
    tmap->door_state = malloc(sizeof(int *) * height);
    tmap->door_timer = malloc(sizeof(double *) * height);
    if (!tmap->door_state || !tmap->door_timer)
	    return (false);
    y = 0;
	while (y < height)
	{
		tmap->door_state[y] = malloc(sizeof(int) * width);
		tmap->door_timer[y] = malloc(sizeof(double) * width);
		if (!tmap->door_state[y] || !tmap->door_timer[y])
			return (1);
		y++;
	}
    init_doors_values(tmap, height, width);
    return (true);
}

static void	update_door_at(t_map *tmap, int y, int x)
{
	if (tmap->door_state[y][x] == DOOR_OPENING)
	{
		tmap->door_timer[y][x] += 0.25;
		if (tmap->door_timer[y][x] >= 1.0)
		{
			tmap->door_timer[y][x] = 1.0;
			tmap->door_state[y][x] = DOOR_OPEN;
		}
	}
	else if (tmap->door_state[y][x] == DOOR_CLOSING)
	{
		tmap->door_timer[y][x] -= 0.25;
		if (tmap->door_timer[y][x] <= 0.0)
		{
			tmap->door_timer[y][x] = 0.0;
			tmap->door_state[y][x] = DOOR_CLOSED;
		}
	}
}

static void update_door(t_map *tmap, int x, int y)
{
    double  dx;
    double  dy;
    double  distt;
    int     st;

    st = tmap->door_state[y][x];
    dx = tmap->player->posx + tmap->player->ray2->offx / tmap->player->ray2->grid;
    dy = tmap->player->posy + tmap->player->ray2->offy / tmap->player->ray2->grid;
    distt = dist(x, y, dx, dy);
    if (distt <= 2.0 && st != DOOR_OPEN && st != DOOR_OPENING)
        tmap->door_state[y][x] = DOOR_OPENING;
    else if (distt > 2.2 && st != DOOR_CLOSED && st != DOOR_CLOSING)
        tmap->door_state[y][x] = DOOR_CLOSING;
    update_door_at(tmap, y, x);
}

void	update_doors(t_map *tmap)
{
	int	y;
	int	x;
    
	y = 0;
	while (y < tmap->count.map_lines)
	{
		x = 0;
		while (x < tmap->count.map_width)
		{
			if (tmap->the_map[y][x] == '2')
                update_door(tmap, x, y);
			x++;
		}
		y++;
	}
}
