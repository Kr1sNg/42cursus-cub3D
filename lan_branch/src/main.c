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
//init map
//drawing map, walls, doors, sky, floor, little map
//locate objets, me, animates...

/* project map:
1. camera setup-build view-frustum: FOV(shiye), ren_width(resolution),
    cam_direct, cam_width
2. image buffer: make_image(), make objects(add_item())?
3. rendering(scene, camera): raycasting/rasterization(casting light), calcul the fix point
    of each object(me, animates, walls, doors, sky, floor, little map...))
4. render it on image buffer(by column or by pixel)

5. door rotate: request_animate(animate rotate x, y)


data->map->object = mlx_xpm_file_to_image(data->mlx, relative_path,
        &img_width, &img_height);
*/

/* 
1. 使用 MiniLibX 库（42 项目的标准图形库）
void    *img;
int     width;
int     height;

img = mlx_xpm_file_to_image(mlx, "crystal_box.xpm", &width, &height);
----------------------------------------------------------------------
2. 从地图中找到 玩家位置,，同时设置朝向
player.posX = col_index + 0.5;
player.posY = row_index + 0.5;
player.dirX = 0;
player.dirY = -1; // 向北
planeX = 0.66; // 摄像平面的向量
planeY = 0;
----------------------------------------------------------------------
3. DDA 算法进行射线投射（Raycasting）
核心部分。每一条垂直屏幕的线，都要从玩家视角发射一条“射线”，直到遇到墙。

for (int x = 0; x < screenWidth; x++) {
    // 计算当前射线方向
    double cameraX = 2 * x / (double)screenWidth - 1;
    rayDirX = player.dirX + planeX * cameraX;
    rayDirY = player.dirY + planeY * cameraX;

    // 起点的格子坐标
    mapX = (int)player.posX;
    mapY = (int)player.posY;

    // 使用 DDA 算法找交点
    ...
    
    // 计算墙高
    int lineHeight = (int)(screenHeight / perpWallDist);

    // 得到墙顶和底
    int drawStart = -lineHeight / 2 + screenHeight / 2;
    int drawEnd = lineHeight / 2 + screenHeight / 2;

    // 根据纹理贴图 crystal_box.xpm 取样贴图坐标
    ...
}
----------------------------------------------------------------------
4. 在每条屏幕垂线渲染时，先绘制天花板和地板：
// 天空色 RGB(225,30,0)
for (int y = 0; y < drawStart; y++)
    pixel_put(x, y, create_rgb(225, 30, 0));

// 地面色 RGB(220,100,0)
for (int y = drawEnd; y < screenHeight; y++)
    pixel_put(x, y, create_rgb(220, 100, 0));
----------------------------------------------------------------------
5. 绘制墙体纹理:根据 DDA 算法返回的交点，选择 crystal_box.xpm 中对应的像素进行贴图
int texX = ...; // 纹理的横坐标
for (int y = drawStart; y < drawEnd; y++) {
    int texY = ((y - drawStart) * textureHeight) / lineHeight;
    int color = texture[texY * textureWidth + texX];
    pixel_put(x, y, color);
}

完整代码框架（简化）
int main()
{
    t_vars vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "3D Map");

    // 读取纹理
    vars.texture.img = mlx_xpm_file_to_image(vars.mlx, "crystal_box.xpm", &w, &h);
    vars.texture.data = mlx_get_data_addr(vars.texture.img, &bpp, &size_line, &endian);

    // 初始化玩家、地图
    init_map(&vars);
    init_player(&vars);

    // 主循环
    mlx_loop_hook(vars.mlx, &render_frame, &vars);
    mlx_loop(vars.mlx);
}

 */

//	int	rgb[3]; 

/* int	find_elem(char	*line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] && line[i] == 'F')
		return (5);
	else if (line[i] && line[i] == 'C')
		return (6);
	else if (line[i] && line[i] == 'N' && line[i + 1] && line[i + 1] == 'O')
		return (1);
	else if (line[i] && line[i] == 'S' && line[i + 1] && line[i + 1] == 'O')
		return (2);
	else if (line[i] && line[i] == 'W' && line[i + 1] && line[i + 1] == 'E')
		return (3);	
	else if (line[i] && line[i] == 'E' && line[i + 1] && line[i + 1] == 'A')
		return (4);
	else
		return (0);	
}

t_map	*extract_map(char	*path)
{
	int		fd;
	char	*line;
	t_map	*tmap;
	int		ele;

	fd = open(path, O_RDONLY);
	if (!fd)
		return (perror("Cube3D: .cub file"), NULL);
	tmap = malloc(sizeof(t_map));
	if (!tmap)
		return (perror("Cube3D: malloc tmap"), close(fd), NULL);
	line = get_next_line(fd, 0);
	while (line)
	{
		if ((ele = find_elem(line)) != 0)
			add_feature(ele, line, tmap);
		else
			fill_map(line, tmap);
	}
	close(fd);
	return (tmap);
} */
/* int	transfer_arr_map()
{
	
}

int	transfer_llst_map(t_map	*tmap, int	fd)
{
	int		i;
	int		w;
	char	*line;
	t_lmap	*new;
	t_lmap	*head = NULL;
	t_lmap	*curr = NULL;

	tmap->lmap = malloc(sizeof(t_lmap));
	if (!tmap->lmap)
		return (perror("Cube3D: malloc lmap in tmap"), 2);
	i = 0;
	line = get_next_line(fd, 0);
	w = 0;
	while (line)
	{
		new = malloc(sizeof(t_lmap));
		if (!new)
			return (perror("Cube3D: malloc lmap node"), free(line), 3);
		new->line = line;
		new->next = NULL;
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
		if ((int)ft_strlen(tmap->lmap->line) > w)
			w = ft_strlen(tmap->lmap->line);
		i++;
		line = get_next_line(fd, 0);		
	}
	tmap->lmap = head;
	tmap->map_h = i;
	tmap->map_w = w;
	return (0);
}

int	ft_init_map(t_map	*tmap, int	fd)
{	
	int	sign;
	
	tmap = malloc(sizeof(t_map));
	if (!tmap)
		return (perror("Cube3D: malloc tmap"), close(fd), 1);
	ft_memset(tmap, 0, sizeof(t_map));
	sign = transfer_llst_map(tmap, fd);
	if (sign)
		return (close(fd), sign);
	sign = transfer_arr_map(tmap);		
	if(sign)
		return (close(fd), sign);
	return (0);
} */


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