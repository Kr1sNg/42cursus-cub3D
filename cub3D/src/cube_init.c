/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:37:03 by layang            #+#    #+#             */
/*   Updated: 2025/06/18 10:59:15 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_3d.h"

static void	ft_init_map_2(t_map	*tmap, char **mapa)
{
    int	i;
    
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
}

static void	ft_init_map(t_map	*tmap, int	fd)
{	
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
    ft_init_map_2(tmap, mapa);
}

//tmap->color_c = (225 << 16) | (30 << 8) | 0;
//tmap->color_f = (220 << 16) | (100 << 8) | 0;
static void init_map_player(t_map	*tmap)
{
	tmap->player = malloc(sizeof(t_cam));
	if (!tmap->player)
		return (perror("Cube3D: malloc player"), NULL);	
	tmap->player->ray2 = malloc(sizeof(t_raycastor));
	if (!tmap->player->ray2)
		return (perror("Cube3D: malloc ray2"), NULL);
	tmap->player->ray2->offx = 0.0;
	tmap->player->ray2->offy = 0.0;
	tmap->player->posx = 26;
	tmap->player->posy = 11;
	tmap->player->dirx = 0.0;
	tmap->player->diry = -1.0;
	tmap->player->planex = 0.66;
	tmap->player->planey = 0;
	tmap->player->pitch = 0.0;
	tmap->player->p_angle = get_player_angle(tmap->player);
	tmap->player->fov = 66.0 * (M_PI / 180);
	tmap->player->ray_nb = WIDTH;	
}

static void init_map_texture(t_map	*tmap)
{
	int		size;

	size = 64;
	tmap->tex_n.mlx_img = mlx_xpm_file_to_image(mlx, "assets/tree.xpm", &size, &size);
	tmap->tex_s.mlx_img = mlx_xpm_file_to_image(mlx, "assets/colorstone.xpm", &size, &size);	
	tmap->tex_e.mlx_img = mlx_xpm_file_to_image(mlx, "assets/greystone.xpm", &size, &size);
	tmap->tex_w.mlx_img = mlx_xpm_file_to_image(mlx, "assets/mossy.xpm", &size, &size);
	tmap->tex_n.addr = mlx_get_data_addr(tmap->tex_n.mlx_img, &tmap->tex_n.bits_pix,
		&tmap->tex_n.line_len, &tmap->tex_n.endian);
	tmap->tex_s.addr = mlx_get_data_addr(tmap->tex_s.mlx_img, &tmap->tex_s.bits_pix,
		&tmap->tex_s.line_len, &tmap->tex_s.endian);
	tmap->tex_e.addr = mlx_get_data_addr(tmap->tex_e.mlx_img, &tmap->tex_e.bits_pix,
		&tmap->tex_e.line_len, &tmap->tex_e.endian);
	tmap->tex_w.addr = mlx_get_data_addr(tmap->tex_w.mlx_img, &tmap->tex_w.bits_pix,
		&tmap->tex_w.line_len, &tmap->tex_w.endian);	
	tmap->color_c = 0x000066;
	tmap->color_f = 0x9400D3;
	tmap->visible = 10;
}

t_map	*simple_extract_map(void	*mlx, char	*path)
{
	int		fd;
	t_map	*tmap;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Cube3D: .cub file"), NULL);
	tmap = malloc(sizeof(t_map));
	if (!tmap)
		return (perror("Cube3D: malloc tmap"), NULL);
	ft_memset(tmap, 0, sizeof(t_map));
	ft_init_map(tmap, fd);
	close(fd);
	init_map_texture(tmap);
	init_map_player(tmap);
	return (tmap);
}
