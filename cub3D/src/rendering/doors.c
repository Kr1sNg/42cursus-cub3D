/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin < layang@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:34:46 by marvin            #+#    #+#             */
/*   Updated: 2025/06/20 17:34:46 by marvin           ###   ########.fr       */
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

/* void	update_doors(t_map *tmap)
{
	int	y;
	int	x;
	int	height;
	int	width;

	height = tmap->count.map_lines;
	width = tmap->count.map_width;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (tmap->door_state[y][x] == DOOR_OPENING
				|| tmap->door_state[y][x] == DOOR_CLOSING)
			{
				update_door_at(tmap, y, x);
			}
			x++;
		}
		y++;
	}
} */

void	update_doors(t_map *tmap)
{
	int	y;
	int	x;
	int	height;
	int	width;
    int st;
    double dx;
    double dy;
    double  distt;

	height = tmap->count.map_lines;
	width = tmap->count.map_width;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (tmap->the_map[y][x] == '2')
            {
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
			x++;
		}
		y++;
	}
}

/* 
void update_doors(t_map   *tmap)
{
    int	y;
    int	x;
    int height;
    int width;

    height = tmap->count.map_lines;
    width = tmap->count.map_width;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (tmap->door_state[y][x] == DOOR_OPENING)
            {
                tmap->door_timer[y][x] += 0.05; // 控制开门速度
                if (tmap->door_timer[y][x] >= 1.0)
                {
                    tmap->door_timer[y][x] = 1.0;
                    tmap->door_state[y][x] = DOOR_OPEN;
                }
            }
            else if (tmap->door_state[y][x] == DOOR_CLOSING)
            {
                tmap->door_timer[y][x] -= 0.05;
                if (tmap->door_timer[y][x] <= 0.0)
                {
                    tmap->door_timer[y][x] = 0.0;
                    tmap->door_state[y][x] = DOOR_CLOSED;
                }
            }
        }
    }
}


在 raycasting 中使用门的动画状态？
在你的 DDA hit 时，如果你 hit 到的是门（'D'），你就根据 door_timer[y][x] 的值调整门的距离：
if (map[mapY][mapX] == 'D')
{
    hit = 1;
    is_door = 1;

    // 距离 += 开门偏移（比如 0.0 ~ 1.0）
    perp_wall_dist += door_timer[mapY][mapX];
} 
这就实现了门慢慢“缩进去”的动画效果，同时还保持了深度正确性。 
*/
