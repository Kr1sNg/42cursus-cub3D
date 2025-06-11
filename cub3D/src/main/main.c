/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/11 14:36:43 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	loop_img(t_scene *scene)
{
	if (!scene->win)
		return (1);		
	render_background(&scene->img, scene->tmap);
	mouse_rotate(scene);
	put_minimap(scene);
	//p.x = WIDTH / 2;
	//p.y = HEIGHT / 2;
	//map_to_img(&scene->img, scene->tmap, p);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.mlx_img, 0, 0);
	
	//render_instructions(all);
	return (0);
}


int	main(int ac, char **av)
{
	t_scene	scene;
	
	if (ac != 2)
		return (printf("Usage: ./cub3d valid_map.cub"));
	
	scene.mlx = mlx_init();
	if (!scene.mlx)
		return (perror("Cube3D: mlx_init"), 1);
	scene.win = mlx_new_window(scene.mlx, WIDTH, HEIGHT, "Cube 3D");
	if (!scene.win)
		return (mlx_destroy_window(scene.mlx, NULL),
			perror("Cube3D: mlx_new_window"), 1);
			
	scene.tmap = map_init(scene.mlx, av[1]);
	scene.img.mlx_img = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	if (!scene.img.mlx_img)
		return (perror("mlx_new_image"), 1);
	scene.img.addr = mlx_get_data_addr(scene.img.mlx_img, &scene.img.bits_pix,
		&scene.img.line_len, &scene.img.endian);
	// mlx_mouse_move(scene.mlx, scene.win, WIDTH/2, HEIGHT/2);
	hook_controls(&scene);
	mlx_loop_hook(scene.mlx, loop_img, &scene);
	mlx_loop(scene.mlx);
	
	return (0);
}


