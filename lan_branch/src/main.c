/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:27:48 by layang            #+#    #+#             */
/*   Updated: 2025/06/07 15:11:56 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_3d.h"

 static void tt_printmap(char	**map, int	n, int	len_max)
{
	int	i;
	int	j;

	i = 0;
	printf("len max: %d\n", len_max);
	printf("lines: %d\n", n);	
	while (i < n)
	{
		j = 0;
		while (map[i][j] != '\0')
			write(1, &map[i][j++], 1);
		write(1, "\n", 1);
		i++;
	}
}
/* 
 */

static void	ft_init_map(t_map	*tmap, int	fd)
{	
	int	i;
	char *mapa[] = {
		"        1111111111111111111111111",
		"        1000000000110000000000001",
		"        1011000001110000000000001",
		"        1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"11110111111111011100000010001",
		"11110111111111011101010000001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111",
		NULL
	};	
	(void)fd;
	tmap->map_h = 14;
	tmap->map_w = 33;
	tmap->map = malloc(sizeof(char	*) * tmap->map_h);
	if (!tmap->map)
	{
		printf("malloc map failed.\n");
		return ;
	}
	i = 0;
	while (i < tmap->map_h)
	{
		tmap->map[i] = ft_strdup(mapa[i]);
		i++;
	}
	tt_printmap(tmap->map, tmap->map_h, tmap->map_w);
}

static t_map	*simple_extract_map(void	*mlx, char	*path)
{
	int		fd;
	t_map	*tmap;
	int		size;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Cube3D: .cub file"), NULL);
	tmap = malloc(sizeof(t_map));
	if (!tmap)
		return (perror("Cube3D: malloc tmap"), NULL);
	ft_memset(tmap, 0, sizeof(t_map));
	ft_init_map(tmap, fd);
	close(fd);
	size = 64;
	tmap->tex_n = mlx_xpm_file_to_image(mlx, "assets/tree.xpm", &size, &size);
	tmap->tex_s = mlx_xpm_file_to_image(mlx, "assets/colorstone.xpm", &size, &size);	
	tmap->tex_e = mlx_xpm_file_to_image(mlx, "assets/greystone.xpm", &size, &size);
	tmap->tex_w = mlx_xpm_file_to_image(mlx, "assets/mossy.xpm", &size, &size);
	tmap->color_c = 0x000066;
	tmap->color_f = 0x9400D3;
	//tmap->color_c = (225 << 16) | (30 << 8) | 0;
	//tmap->color_f = (220 << 16) | (100 << 8) | 0;
	tmap->player.posx = 26;
	tmap->player.posy = 11;
	tmap->player.dirx = 0;
	tmap->player.diry = -1;
	tmap->player.pitch = 0;
	return (tmap);
}

static int	loop_img(t_scene	*scene)
{
	if (!scene->win)
		return (1);		
	render_background(&scene->img, scene->tmap);
	put_minimap(scene);
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
	scene.planex = 0.66;
	scene.planey = 0;
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

/* 
在真实开发中，为了清晰的图层结构和渲染效率，标准流程是：
背景 → 墙体（逐列射线）→ 精灵（按距离排序）→ 最上层 UI（如 minimap） */
