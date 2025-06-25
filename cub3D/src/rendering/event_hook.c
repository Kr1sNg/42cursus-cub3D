/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:23:26 by layang            #+#    #+#             */
/*   Updated: 2025/06/25 13:19:24 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate(t_scene	*scene, double angl_turn)
{
	scene->tmap->player->p_angle += angl_turn;
	if (scene->tmap->player->p_angle > 2.0 * M_PI)
		scene->tmap->player->p_angle -= 2.0 * M_PI;
	if (scene->tmap->player->p_angle < 0)
		scene->tmap->player->p_angle += 2.0 * M_PI;
	scene->tmap->player->dirx = cos(scene->tmap->player->p_angle);
	scene->tmap->player->diry = -sin(scene->tmap->player->p_angle);		
}

int	key_hooks(int keycode, t_scene	*all)
{
	if (keycode == XK_Escape)
		close_cube3d(all);
	if (keycode == XK_Left)
		rotate(all, 0.05);
	if (keycode == XK_Right)
		rotate(all, -0.05);
	if (keycode == XK_w)
		floating_coord(all->tmap, 12, 0);
	if (keycode == XK_s)
		floating_coord(all->tmap, -12, 0);
	if (keycode == XK_d)
		floating_coord(all->tmap, 12, 1);
	if (keycode == XK_a)
		floating_coord(all->tmap, -12, 1);
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
	mlx_hook(scene->win, KeyPress, KeyPressMask, key_hooks, scene);
	mlx_mouse_move(scene->mlx, scene->win, WIDTH/2, HEIGHT/2);
	// mlx_mouse_hide(scene->mlx, scene->win); //- it causes some leaks
}
