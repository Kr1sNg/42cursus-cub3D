/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:48:19 by layang            #+#    #+#             */
/*   Updated: 2025/06/10 15:16:58 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdarg.h>

# define WIDTH			1920
# define HEIGHT			1080
//# define WIDTH			920
//# define HEIGHT			680
# define WHITE			0x00FFFFFF

typedef enum e_hit
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_hit;

typedef struct s_point
{
	int		x;
	int		y;
	int		color;
}	t_point;

typedef	struct s_lmap
{
	char			*line;
	struct s_lmap	*next;
}	t_lmap;

typedef	struct s_cam
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double  p_angle;
	int		pitch;
	double  fov;
	int		ray_nb;
}	t_cam;

typedef	struct s_map
{
	void	*tex_n;
	void	*tex_s;
	void	*tex_w;
	void	*tex_e;
	int		color_f;
	int		color_c;
	char	**map;
	t_lmap	*lmap;
	int		map_h;
	int		map_w;
	t_cam	player;
}	t_map;

//pitch: 玩家视角的俯仰角（上下看）for sky and floor: 
// y_offset = (screen_height / 2) + player->pitch;	
typedef struct s_raycastor
{
	double	start_angle;
	double	angle_step;
	int		grid;
	double	ra;
	int		dof;	
	double	disH;
	double	disV;
	double	dist;
	double	rx;
	double	ry;
	double	final_x;
	double	final_y;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	double	stepx;
	double	stepy;
	t_hit	hit;
	t_point	in_map;	
}	t_raycastor;

typedef struct s_pic
{
	void	*mlx_img;
	void	*addr;
	int		bits_pix;
	int		line_len;
	int		endian;
}	t_pic;

typedef	struct s_scene
{
	t_map	*tmap;
	t_pic	img;
	void	*mlx;
	void	*win;
}	t_scene;


/* 这是一个非常关键的问题，说明你已经开始理解 射线投射（Raycasting） 和 纹理映射（Texture Mapping） 之间的联系了。

🌐 总体关系
DDA 算法（Digital Differential Analyzer） 的作用是：

沿着视角方向（射线）从玩家位置向前推进。

找到射线击中的第一个“墙”的位置（在地图中是一个 1）。

得到这个交点所在的 地图格子（tile） 和具体的 墙面命中位置。

纹理坐标（UV） 的作用是：

将你“击中的那面墙”对应到纹理图片上的某一列像素（U方向）。

然后根据每个垂直像素的高度，从纹理中取一列数据画出来（V方向）。

📌 一步步说明关系
① 使用 DDA 找到射线撞墙的点
例如射线从玩家位置 (posX, posY) 向一个方向 (rayDirX, rayDirY) 发射。

DDA 会推进 mapX / mapY，直到地图中 map[mapX][mapY] == '1'。

同时记录这条射线是撞到了 哪一面墙（南北墙 or 东西墙）。

② 根据撞击点计算 U 坐标
射线撞到墙时，我们可以得到精确的命中位置 wallX。

如果撞到 竖墙（东西墙），就用 posY + perpWallDist * rayDirY 得到 Y 命中位置。

如果撞到 横墙（南北墙），就用 posX + perpWallDist * rayDirX 得到 X 命中位置。

然后只保留小数部分：wallX -= floor(wallX)，这就是 纹理的横坐标（U）。

③ 将 U 转换成纹理图片的横向像素位置
假设你纹理宽度为 texWidth = 64

则纹理列号是：texX = (int)(wallX * texWidth)

④ 垂直绘制墙时，从上往下采样纹理（V方向）
你计算出墙在屏幕上的绘制高度为 lineHeight

每个屏幕像素在墙体上对应纹理中的一个 V 值，通过如下方式获得：

texY = ((y * 2 - screenHeight + lineHeight) * texHeight) / (2 * lineHeight);
最终从 texture[texX][texY] 获取像素颜色，绘制到屏幕。

🔁 总结关系：
DDA 射线投射得到的内容	用于纹理映射的作用
墙体的地图坐标 mapX, mapY	知道在哪面墙贴图
撞击点 wallX	得到纹理横坐标 U
撞到墙的方向（东西 or 南北）	决定 wallX 使用 posY 还是 posX
墙在屏幕的高度 lineHeight	决定如何从纹理图采样 V

如果你愿意，我可以根据你的 .xpm 文件直接写一段 DDA + 纹理映射 的完整代码示例。需要吗？ */

/*
---------------------------------------------------
lineHeight = (int)(screenHeight / perpWallDist);
screenHeight：你的窗口高度（以像素为单位），比如 480 或 720。

perpWallDist（perpendicular wall distance）：从玩家位置到墙体的垂直距离，即 视线方向上的距离。

lineHeight：这个射线要在屏幕上绘制的墙的垂直像素数。

假设你的玩家离墙很近，perpWallDist = 1.0，screenHeight = 480：

c
Copy
Edit
lineHeight = 480 / 1.0 = 480  // 墙画满整个屏幕（就在你眼前）
远一点，perpWallDist = 2.0：

c
Copy
Edit
lineHeight = 480 / 2.0 = 240  // 只画一半高，看起来远了一点
更远，perpWallDist = 6.0：

c
Copy
Edit
lineHeight = 480 / 6.0 = 80   // 更小，看起来更远
这就是模拟 3D 的核心机制之一！

🔍 perpWallDist 是怎么来的？
在使用 DDA 算法找到撞墙格子之后，你可以这样计算：

c
Copy
Edit
if (side == 0)
    perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
else
    perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
side == 0 表示撞的是垂直墙（东西墙）

side == 1 表示撞的是水平墙（南北墙）

这个公式考虑了从 posX/Y 到下一个格子中心的距离，模拟真实的“直线距离”。

🧠 总结
c
Copy
Edit
lineHeight = screenHeight / perpWallDist;
射线距离越远，墙看起来越矮。

射线距离越近，墙看起来越高。

这就是 Raycasting 最重要的视觉透视基础之一。
*/

/* main.c 5*/

/* minimap.c 2*/
void	put_minimap(t_scene	*scene);

/* minimap_utils.c 3*/
int		inside_map_array(int x, int y, t_scene *scene);
void	draw_square(t_scene	*scene, t_point p, int size);
void	draw_line(t_scene	*scene, t_point	s, t_point	e, int	color);
void	draw_player_vector(t_scene	*scene, t_point player, int	len);
void	draw_player_vision(t_scene *scene, t_point p, int grid);

/* cube_utils.c 5*/
double	get_player_angle(t_cam player);
void	put_pixel(t_pic	*img, t_point	pt);
void	render_background(t_pic	*img, t_map	*tmap);
void	rotate(t_scene	*scene, double angl_turn);
void	translate(t_map	*tmap, t_point	mov);

/* event_hook.c 2*/
int		key_hooks(int keycode, t_scene	*all);
void	hook_controls(t_scene	*scene);

/* cube_free.c 5*/
void	free_arr(char	***paths);
void	free_lst(t_lmap	**tokens);
int		close_cube3d(t_scene	*scene);

/* minimap.c 3*/

#endif
