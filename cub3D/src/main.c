/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:27:48 by layang            #+#    #+#             */
/*   Updated: 2025/06/18 10:40:41 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_3d.h"

static int	loop_img(t_scene	*scene)
{
	if (!scene->win)
		return (1);		
	//render_background(&scene->img, scene->tmap);
	draw_maps(scene);
	//p.x = WIDTH / 2;
	//p.y = HEIGHT / 2;
	//map_to_img(&scene->img, scene->tmap, p);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.mlx_img, 0, 0);
	//render_instructions(all);
	return (0);
}


int	main(int ac, char	**av)
{
	t_scene	scene;
	
	(void)ac;
	scene.mlx = mlx_init();
	if (!scene.mlx)
		return (perror("Cube3D: mlx_init"), 1);
	scene.win = mlx_new_window(scene.mlx, WIDTH, HEIGHT, "Cube 3D");
	if (!scene.win)
		return (mlx_destroy_window(scene.mlx, NULL),
			perror("Cube3D: mlx_new_window"), 1);
	scene.tmap = simple_extract_map(scene.mlx, av[1]);
	if (!scene.tmap)
		return(printf("Oh NO, no tmap pointer\n"), 0);
	scene.img.mlx_img = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	if (!scene.img.mlx_img)
		return (perror("Cube3D: mlx_new_image"), 1); 
	// free tmap, free_cube(&scene.tmap, &scene.mlx),
	// mlx_destroy_window(scene.mlx,scene.win)
	scene.img.addr = mlx_get_data_addr(scene.img.mlx_img, &scene.img.bits_pix,
		&scene.img.line_len, &scene.img.endian);
	hook_controls(&scene);
	mlx_loop_hook(scene.mlx, loop_img, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
