/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:23:26 by layang            #+#    #+#             */
/*   Updated: 2025/06/07 14:23:52 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_3d.h"

int	key_hooks(int keycode, t_scene	*all)
{
	if (keycode == XK_Escape)
		close_cube3d(all);
/* 	if (keycode == XK_equal)
		zoom(all->map, 1.2);
	if (keycode == XK_minus)
		zoom(all->map, 1 / 1.2); */
/* 	if (keycode == XK_Left)
		translate(all->map, (t_point){-10, 0, 0, 0});
	if (keycode == XK_Right)
		translate(all->map, (t_point){10, 0, 0, 0});
	if (keycode == XK_Up)
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

void	hook_controls(t_scene	*scene)
{
	mlx_hook(scene->win, DestroyNotify, 0, close_cube3d, scene);
	mlx_key_hook(scene->win, key_hooks, scene);
}
