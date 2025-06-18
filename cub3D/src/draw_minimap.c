/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:43:05 by layang            #+#    #+#             */
/*   Updated: 2025/06/18 12:42:36 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_3d.h"

static void	renew_err_s(int *err, t_point   *s, t_point	delta, t_point	sign)
{
    int err2;
    
    err2 = 2 * (*err);
    if (err2 > -delta.y)		
    {
        *err -= delta.y;
        (*s).x += sign.x;
    }
    if (err2 < delta.x)		
    {
        *err += delta.x;
        (*s).y += sign.y;
    }
}

void	line_bh(t_scene	*scene, t_point	s, t_point	e, t_raycastor	*cast)
{
	int	err;
	t_point	delta;
	t_point	sign;

	s.color = e.color;
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
		if (s.x >= cast->offset.x && s.y >= cast->offset.y
				&& s.x <= cast->offset.x + cast->grid * 10
				&& s.y <= cast->offset.y + cast->grid * 10)
			put_pixel(&scene->img, s);
		if (s.x == e.x && s.y == e.y)
			break ;
        renew_err_s(&err, &s, delta, sign);
	}
}

static void	draw_ray_line(t_raycastor	*cast, t_scene *scene, t_point p, int col)
{
	int	x;
	int	y;

    get_correct_dist(cast);
	x = floor(cast->final_x) + cast->offset.x;
	y = floor(cast->final_y) + cast->offset.y;
	p.x += cast->offset.x;
	p.y += cast->offset.y;
	line_bh(scene, p, (t_point){x, y, col}, cast);
}

static void dda_raycasting_2d(t_raycastor	*cast, t_scene *s, int r, t_point p)
{
    double	off_r;
	int		depth;
	int		n;

    n = s->tmap->player->ray_nb;
    off_r = ((double)r / (n - 1)) * cast->fov - (cast->fov / 2.0);
    cast->ra = normalize_angle(s->tmap->player->p_angle + off_r);
    init_raycastor(p, cast);
    intersect_h(cast, p, &depth);
    get_dis_h(cast, s, p, &depth);
    intersect_v(cast, p, &depth);
    get_dis_v(cast, s, p, &depth);
    draw_ray_line(cast, s, p, 0xFF9999);
}

void	draw_player_vision(t_scene *scene, t_point p, int grid, t_point	off)
{
	t_raycastor	*cast;
	int		r;
	int		n;
	double	off_r;
	int		depth;
	
	cast = scene->tmap->player->ray2;
	cast->ra = scene->tmap->player->p_angle;
	r = 0;
	p.x -= off.x;
	p.y -= off.y;
	cast->offset.x = off.x;
	cast->offset.y = off.y;
	n = scene->tmap->player->ray_nb;
	while (r < n)
	{
        dda_raycasting_2d(cast, scene, r, p);
		r++;
	}
}
