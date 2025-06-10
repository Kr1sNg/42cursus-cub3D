/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:20:17 by layang            #+#    #+#             */
/*   Updated: 2025/06/10 17:52:32 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	inside_map_array(int x, int y, t_scene *scene)
{
	if (x < 0 || y < 0)
		return (0);
	if (y >= scene->tmap->count.map_lines)
		return (0);
	if (x >= (int)ft_strlen(scene->tmap->the_map[y]))
		return (0);
	return (1);
}

void draw_square(t_scene	*scene, t_point p, int size)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(&scene->img, (t_point){p.x + i, p.y + j, p.color});
			j++;
		}
		i++;
	}
}

void	draw_line(t_scene	*scene, t_point	s, t_point	e, int	color)
{
	int	err;
	int	err2;
	t_point	delta;
	t_point	sign;

	s.color = color;
	delta.x = abs(e.x - s.x);
	delta.y = abs(e.y - s.y);
	err = delta.x - delta.y;
	sign.x = -1;
	if (s.x < e.x)
		sign.x = 1;
	sign.y = -1;
	if (s.y < e.y)
		sign.y = 1;
	while (1)
	{
		put_pixel(&scene->img, s);
		if (s.x == e.x && s.y == e.y)
			break ;
		err2 = 2 * err;
		if (err2 > -delta.y)		
		{
			err -= delta.y;
			s.x += sign.x;
		}
		if (err2 < delta.x)		
		{
			err += delta.x;
			s.y += sign.y;
		}
	}
}

void	draw_player_vector(t_scene	*scene, t_point player, int	len)
{
	double	p_angle;
	t_point vec;

	p_angle = scene->tmap->player.p_angle;
	vec.x = (int)(player.x + cos(p_angle) * len);
	vec.y = (int)(player.y - sin(p_angle) * len);
	draw_line(scene, player, vec, player.color);
}

static double dist(double sx, double sy, double ex, double ey)
{
	return (sqrt((ex - sx) * (ex - sx) + (ey - sy) * (ey - sy)));
}

static void	init_raycastor(t_scene *scene, t_point p, t_raycastor	*cast)
{
	cast->ra = scene->tmap->player.p_angle;
	cast->start_angle = scene->tmap->player.p_angle - scene->tmap->player.fov / 2;
	cast->angle_step = scene->tmap->player.fov / scene->tmap->player.ray_nb;
	cast->disH = 1e6;
	cast->disV = 1e6;
	cast->dof = 5;
	cast->hx = p.x;
	cast->hy = p.y;
	cast->vx = p.x;
	cast->vy = p.y;	
}

static void	intersect_v(t_raycastor	*cast, t_point p, int *depth)
{
	double	atan;
	
	*depth = 0;
	//atan = -tan(cast->ra);
	atan = -1 / tan(cast->ra);
	if ((cast->ra > M_PI / 2) && (cast->ra < 3 * M_PI / 2))
	{
		cast->rx = ((int)(p.x) / cast->grid) * cast->grid - 0.0001;
		cast->ry = (p.x - cast->rx) * atan + p.y;
		cast->stepx = -cast->grid;
		cast->stepy = cast->stepx * atan;
	}
	else if ((cast->ra < M_PI / 2) || (cast->ra > 3 * M_PI / 2))
	{
		cast->rx = ((int)(p.x) / cast->grid) * cast->grid + cast->grid;
		cast->ry = (p.x - cast->rx) * atan + p.y;
		cast->stepx = cast->grid;
		cast->stepy = cast->stepx * atan;
	}
	else
	{
		cast->rx = p.x;
		cast->ry = p.y;
		*depth = 8;
	}
}

static void	get_dis_v(t_raycastor	*cast, t_scene *scene, t_point p, int *depth)
{
	while (*depth < cast->dof)
	{
		cast->in_map.x = (int)(cast->rx) / cast->grid;
		cast->in_map.y = (int)(cast->ry) / cast->grid;

		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
				&& scene->tmap->the_map[cast->in_map.y][cast->in_map.x] == '1')
		{
			cast->vx = cast->rx;
			cast->vy = cast->ry;
			cast->disV = dist(p.x, p.y, cast->vx, cast->vy);
			*depth = 8;
		}
		else
		{
			cast->rx += cast->stepx;
			cast->ry += cast->stepy;
			(*depth)++;
		}
	}	
}

static void	intersect_h(t_raycastor	*cast, t_point p, int *depth)
{
	double	atan;
	
	*depth = 0;
	//atan = -1 / tan(cast->ra);
	atan = -tan(cast->ra);
	if (cast->ra > M_PI)
	{
		cast->ry = ((int)(p.y) / cast->grid) * cast->grid - 0.0001;
		cast->rx = (p.y - cast->ry) * atan + p.x;
		cast->stepy = -cast->grid;
		cast->stepx = cast->stepy * atan;
	}
	else if (cast->ra < M_PI)
	{
		cast->ry = ((int)(p.y) / cast->grid) * cast->grid + cast->grid;
		cast->rx = (p.y - cast->ry) * atan + p.x;
		cast->stepy = cast->grid;
		cast->stepx = cast->stepy * atan;
	}
	else
	{
		cast->rx = p.x;
		cast->ry = p.y;
		*depth = 8;
	}
}

static void	get_dis_h(t_raycastor	*cast, t_scene *scene, t_point p, int *depth)
{
	while (*depth < cast->dof)
	{
		cast->in_map.x = (int)(cast->rx) / cast->grid;
		cast->in_map.y = (int)(cast->ry) / cast->grid;

		if (inside_map_array(cast->in_map.x, cast->in_map.y, scene)
				&& scene->tmap->the_map[cast->in_map.y][cast->in_map.x] == '1')
		{
			cast->hx = cast->rx;
			cast->hy = cast->ry;
			cast->disH = dist(p.x, p.y, cast->hx, cast->hy);
			*depth = 8;
		}
		else
		{
			cast->rx += cast->stepx;
			cast->ry += cast->stepy;
			(*depth)++;
		}
	}	
}

static void	draw_ray_line(t_raycastor	cast, t_scene *scene, t_point p, int col)
{
	int	x;
	int	y;
	
	if (cast.disV < cast.disH)
	{
		cast.final_x = cast.vx;
		cast.final_y = cast.vy;
	}
	else
	{
		cast.final_x = cast.hx;
		cast.final_y = cast.hy;		
	}
	x = (int)cast.final_x;
	y = (int)cast.final_y;
	draw_line(scene, p, (t_point){x, y, 0}, col);
}

void	draw_player_vision(t_scene *scene, t_point p, int grid)
{
	t_raycastor	cast;
	int		r;
	int		depth;
	
	init_raycastor(scene, p, &cast);
	cast.grid = grid;
	r = 0;
	while (r < scene->tmap->player.ray_nb)
	{
		cast.ra = cast.start_angle + r * cast.angle_step;
		if (cast.ra < 0)
			cast.ra += 2 * M_PI;
		if (cast.ra > 2 * M_PI)
			cast.ra -= 2 * M_PI;
		intersect_h(&cast, p, &depth);
		get_dis_h(&cast, scene, p, &depth);
		intersect_v(&cast, p, &depth);
		get_dis_v(&cast, scene, p, &depth);
		draw_ray_line(cast, scene, p, 0xEBDEF0);
		r++;
	}
}

/* void	draw_player_vision(t_scene *scene, t_point p, int grid)
{
	t_raycastor	cast;
	int		r;
	int		depth;
	
	init_raycastor(scene, p, &cast);
	cast.grid = grid;
	r = 0;
	while (r < scene->tmap->player.ray_nb)
	{
		cast.ra = cast.start_angle + r * cast.angle_step;
		if (ra < 0)
			ra += 2 * M_PI;
		if (ra > 2 * M_PI)
			ra -= 2 * M_PI;
		// 水平交点计算intersect_h
		intersect_h(&cast, scene, p, &depth);
		int depth = 0;
		double disH = 1e6, hx = p.x, hy = p.y;
		double disV = 1e6, vx = p.x, vy = p.y;
		double rx, ry, xo, yo;

		// 水平交点计算
		double atan = -1 / tan(ra);
		if (ra > PI)
		{
			ry = ((int)(p.y) / grid) * grid - 0.0001;
			rx = (p.y - ry) * atan + p.x;
			yo = -grid;
			xo = yo * atan;
		}
		else if (ra < PI)
		{
			ry = ((int)(p.y) / grid) * grid + grid;
			rx = (p.y - ry) * atan + p.x;
			yo = grid;
			xo = yo * atan;
		}
		else
		{
			rx = p.x;
			ry = p.y;
			dof = 8;
		}

		// get_dis_h(&cast, scene)
		while (depth < 8)
		{
			int mx = (int)(rx) / grid;
			int my = (int)(ry) / grid;

			if (inside_map_array(mx, my, scene)
					&& scene->tmap->map[my][mx] == '1') //inside_map_array
			{
				hx = rx;
				hy = ry;
				disH = dist(p.x, p.y, hx, hy);
				depth = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				depth++;
			}
		}

		// 垂直交点计算
		depth = 0;
		atan = -tan(ra);
		if (ra > M_PI / 2 && ra < 3 * PI / 2)
		{
			rx = ((int)(p.x) / grid) * grid - 0.0001;
			ry = (p.x - rx) * atan + p.y;
			xo = -grid;
			yo = xo * atan;
		}
		else if (ra < M_PI / 2 || ra > 3 * PI / 2)
		{
			rx = ((int)(p.x) / grid) * grid + grid;
			ry = (p.x - rx) * atan + p.y;
			xo = grid;
			yo = xo * atan;
		}
		else
		{
			rx = p.x;
			ry = p.y;
			depth = 8;
		}

		//get_dis_v
		while (depth < 8)
		{
			int mx = (int)(rx) / grid;
			int my = (int)(ry) / grid;

			if (inside_map_array(mx, my, scene)
				&& scene->tmap->map[my][mx] == '1') //inside_map_array
			{
				vx = rx;
				vy = ry;
				disV = dist(p.x, p.y, vx, vy);
				depth = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				depth++;
			}
		}

		double final_rx = (disV < disH) ? vx : hx;
		double final_ry = (disV < disH) ? vy : hy;
		draw_line(scene, p, (t_point){(int)final_rx, (int)final_ry, 0}, 0xEBDEF0);
		r++;
	}
} */

