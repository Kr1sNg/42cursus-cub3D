/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:23:26 by layang            #+#    #+#             */
/*   Updated: 2025/06/11 14:42:32 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_hooks(int keycode, t_scene	*all)
{
	if (keycode == XK_Escape)
		close_cube3d(all);
/* 	if (keycode == XK_equal)
		zoom(all->map, 1.2);
	if (keycode == XK_minus)
		zoom(all->map, 1 / 1.2); */
	if (keycode == XK_Left)
		rotate(all, -0.1);
	if (keycode == XK_Right)
		rotate(all, 0.1);
/* 		if (keycode == XK_Up)
		translate(all->map, (t_point){0, -10, 0, 0});
	if (keycode == XK_Down)
		translate(all->map, (t_point){0, 10, 0, 0}); */
	if (keycode == XK_w)
		translate(all->tmap, (t_point){0, -1, 0});
	if (keycode == XK_s)
		translate(all->tmap, (t_point){0, 1, 0});
	if (keycode == XK_d)
		translate(all->tmap, (t_point){1, 0, 0});
	if (keycode == XK_a)
		translate(all->tmap, (t_point){-1, 0, 0});
/* 	if (keycode == XK_x)
		rotate_x(all->map, -0.1);
	if (keycode == XK_s)
		rotate_x(all->map, 0.1);
	else
		key_hooks_2(keycode, all); */
	return (0);
}

int	mouse_rotate(t_scene *all)
{
	int	x;
	int	y;
	int	dx;

	mlx_mouse_get_pos(all->mlx, all->win, &x, &y);
	dx = x - WIDTH / 2;
	rotate(all, dx *(-(2 *M_PI / 11520)));
	mlx_mouse_move(all->mlx, all->win, WIDTH/2, HEIGHT/2);
	return (0);	
}


void	hook_controls(t_scene	*scene)
{
	mlx_hook(scene->win, DestroyNotify, 0, close_cube3d, scene);
	mlx_key_hook(scene->win, key_hooks, scene);
	mlx_mouse_move(scene->mlx, scene->win, WIDTH/2, HEIGHT/2);
	// mlx_mouse_hide(scene->mlx, scene->win); - it causes some leaks
}
