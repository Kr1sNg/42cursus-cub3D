/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/24 17:04:08 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_img(void *mlx, t_pic *image, char *path)
{
	(*image).mlx_img = mlx_xpm_file_to_image(mlx, path, &(*image).width,
			&(*image).height);
	if (!(*image).mlx_img)
		return (false);
	(*image).addr = mlx_get_data_addr((*image).mlx_img, &(*image).bits_pix,
			&(*image).line_len, &(*image).endian);
	if (!(*image).addr)
		return (mlx_destroy_image(mlx, (*image).mlx_img), false);
	return (true);
}

static bool	img_init(void *mlx, t_map *tmap)
{
	if (!check_img(mlx, &tmap->tex_e, tmap->path_e)
		|| !check_img(mlx, &tmap->tex_n, tmap->path_n)
		|| !check_img(mlx, &tmap->tex_s, tmap->path_s)
		|| !check_img(mlx, &tmap->tex_w, tmap->path_w)
		|| !check_img(mlx, &tmap->door, "textures/Door1.xpm")
		|| !check_img(mlx, &tmap->sprite, "textures/KeyFly1.xpm"))
		return (false);
	return (true);
}

static bool	player_init(t_map *tmap)
{
	tmap->player = malloc(sizeof(t_cam));
	if (!tmap->player)
		return (print_err("Cube3D: malloc player"), false);
	tmap->player->ray2 = malloc(sizeof(t_raycastor));
	if (!tmap->player->ray2)
		return (print_err("Cube3D: malloc ray2"), false);
	if (!init_doors(tmap))
		return (print_err("Cube3D: doors initiation"), false);
	tmap->player->ray2->offx = 0.0;
	tmap->player->ray2->offy = 0.0;
	tmap->player->planex = -tmap->count.map_diry * 0.66;
	tmap->player->planey = tmap->count.map_dirx * 0.66;
	tmap->player->pitch = 0.0;
	tmap->player->p_angle = get_player_angle(tmap);
	tmap->player->fov = 66.0 * (M_PI / 180);
	tmap->player->ray_nb = WIDTH;
	tmap->visible = 10;
	tmap->player->dirx = tmap->count.map_dirx;
	tmap->player->diry = tmap->count.map_diry;
	tmap->player->posx = tmap->count.map_posx;
	tmap->player->posy = tmap->count.map_posy;
	return (true);
}

static int	loop_img(t_scene *scene)
{
	if (!scene->win)
		return (1);
	update_doors(scene->tmap);
	draw_maps(scene);
	mouse_rotate(scene);
	animated_sprit(scene->mlx, scene->tmap);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.mlx_img, 0, 0);
	return (0);
}

int	main(int ac, char	**av)
{
	t_scene	scene;

	if (ac != 2)
		return (printf("Usage: ./cub3d valid_map.cub"));
	if (ft_parsing(av[1], &scene) != 0)
		return (free_map_data(scene.tmap), 1);
	scene.mlx = mlx_init();
	if (!scene.mlx)
		return (perror_and_exit(&scene, "Cube3D: mlx_init"), 1);
	scene.win = mlx_new_window(scene.mlx, WIDTH, HEIGHT, "Cube 3D");
	if (!scene.win)
		return (perror_and_exit(&scene, "Cube3D: mlx_new_window"), 1);
	if (!img_init(scene.mlx, scene.tmap))
		return (perror_and_exit(&scene, "Invalid image"), 1);
	if (!player_init(scene.tmap))
		return (perror_and_exit(&scene, NULL), 1);
	scene.img.mlx_img = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	if (!scene.img.mlx_img)
		return (perror_and_exit(&scene, "mlx_new_image"), 1);
	scene.img.addr = mlx_get_data_addr(scene.img.mlx_img, &scene.img.bits_pix,
			&scene.img.line_len, &scene.img.endian);
	hook_controls(&scene);
	mlx_loop_hook(scene.mlx, loop_img, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
