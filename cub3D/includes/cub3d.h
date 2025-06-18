/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:34:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/18 17:19:07 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/time.h>
# include <math.h>
# include <X11/X.h> // macOS
# include <X11/keysym.h> // macOS

# define MAX_LINES	1024

//# define WIDTH		920
//# define HEIGHT		680
# define WIDTH			1920
# define HEIGHT			1080

# define WHITE			0xFFFFFF
# define BLACK			0x000000
# define PURPLE			0x9400D3

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

typedef enum e_hit
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DEFAULT = -1
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

typedef struct s_pic
{
	void	*mlx_img;
	void	*addr;
	int		bits_pix;
	int		line_len;
	int		endian;
}	t_pic;

typedef struct s_count
{
	int		no_line;
	int		so_line;
	int		we_line;
	int		ea_line;
	int		f_line;
	int		c_line;
	int		map_lines; //map_h
	int		map_width; //map_w include space
	int		player_count; // S, W, E, N
}	t_count;

typedef struct s_raycastor
{
	double	offx;
	double	offy;
	double	fov;
	int		grid;
	double	ra;
	double	dirx;
	double	diry;
	int		dof;
	int		pix_ray;
	int		rend_h;
	int		ori_rend_h;
	double	step_tt;
	double	offh;
	int		ori_off;
	int		draw_off;
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
	t_hit	vhit;
	t_hit	hhit;
	t_hit	hit;
	t_point	offset;
	t_point	in_map
}	t_raycastor;

typedef	struct s_cam
{
	int			posx; // horizontal
	int			posy; //  vertical
	double		dirx; // N=(dirx = 0, diry = -1), S=(dirx = 0, diry = 1)
	double		diry; // W=(dirx = -1, diry = 0), E=(dirx = 1, diry = 0)
	t_raycastor	*ray2;
	int			grid;
	double		planex;
	double		planey;
	double  	p_angle;
	double		pitch;
	double  	fov;
	int			ray_nb;	
}	t_cam;

typedef struct s_map
{
	t_pic	door; //2
	t_pic	sprite; //3
	t_pic	tex_n;
	t_pic	tex_s;
	t_pic	tex_w; //image
	t_pic	tex_e;
	char	*path_n; //need to free
	char	*path_s; //need to free
	char	*path_w; //need to free
	char	*path_e; //need to free
	int		color_f;
	int		color_c;
	char	**the_map;
	char	**map_copy;
	t_cam	*player;
	t_count	count; // you can find map_h, map_w here
	int		visible;
}	t_map;

typedef	struct s_scene
{
	t_map	*tmap;
	t_pic	img;
	void	*mlx;
	void	*win;
}	t_scene;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/* parsing */
// error_map
void	perror_and_exit(t_scene *scene, char *str);
void	print_err(char *str);
// free_map
void	free_map_data(t_map *tmap);
//is_line
int		is_texture_line(char *line);
int		is_color_line(char *line);
bool	is_empty_line(char *line);
bool	is_map_line(char *s);
//floodfill
bool	is_closed_map(t_map *tmap, char **lines);
// player
bool	has_located_player(t_map *tmap);
//pars_lines
bool	parse_texture_line(t_map *tmap, char **lines, int i);
bool	parse_color_line(t_map *tmap, char **lines, int i);
//parse_map
int		parse_map_block(t_map *tmap, char **lines);
int		is_valid_map(t_map *tmap, char **lines);
// parsing
int		ft_parsing(char *path, t_scene *scene);
//read_file
bool	is_cub_file(char *path);
char	**read_file(char *path);
//utils
int		color_toi(char **split);
void	print_map(t_scene *scene);

/*main
t_map	*map_init(t_scene *scene, char *path);*/

/* minimap.c 2*/
//void	put_minimap(t_scene	*scene);

/* minimap_utils.c 3
int		inside_map_array(int x, int y, t_scene *scene);
void	draw_square(t_scene	*scene, t_point p, int size);
void	draw_line(t_scene	*scene, t_point	s, t_point	e, int	color);
void	draw_player_vector(t_scene	*scene, t_point player, int	len);
void	draw_player_vision(t_scene *scene, t_point p, int grid);*/

/* cube_utils.c 5
double	get_player_angle(t_cam *player);
void	put_pixel(t_pic	*img, t_point	pt);
void	render_background(t_pic	*img, t_map	*tmap);
void	rotate(t_scene	*scene, double angl_turn);
void	translate(t_map	*tmap, t_point	mov);*/

/* event_hook.c 2
int		key_hooks(int keycode, t_scene	*all);
void	hook_controls(t_scene	*scene);
int		mouse_rotate(t_scene *all);*/

/* cube_free.c 5
void	free_arr(char ***paths);
void	free_lst(t_lmap	**tokens);
int		close_cube3d(t_scene *scene); */

/* draw_3d.c 5 ok*/
void	get_correct_dist(t_raycastor	*cast);
void	draw_3d_scene(t_scene *scene, t_point p, int grid, t_point	off);

/*draw_minimap.c 5 ok*/
void	line_bh(t_scene	*scene, t_point	s, t_point	e, t_raycastor	*cast);
void	draw_player_vision(t_scene *scene, t_point p, int grid, t_point	off);

/* draw_maps.c 4 ok*/
void	draw_maps(t_scene	*scene);

/* minimap_utils.c 5 ok*/
int		inside_map_array(int x, int y, t_scene *scene);
void	draw_square(t_scene	*scene, t_point p, int size);
void	draw_player_vector(t_scene	*scene, t_point player, int	len);
double	dist(double sx, double sy, double ex, double ey);
void	init_raycastor(t_point p, t_raycastor	*cast);

/*raycast_utils.c 5 ok*/
void	intersect_v(t_raycastor	*cast, t_point p, int *depth);
void	get_dis_v(t_raycastor	*cast, t_scene *scene, t_point p, int *depth);
void	intersect_h(t_raycastor	*cast, t_point p, int *depth);
void	get_dis_h(t_raycastor	*cast, t_scene *scene, t_point p, int *depth);

/* cube_utils.c 4 okk*/
int		gradient_color(float_t	r, int s, int e);
double	normalize_angle(double angle);
double	get_player_angle(t_cam *player);
void	put_pixel(t_pic	*img, t_point	pt);

/*draw_textures.c 4 okk*/
void	put_pixel_texture(t_scene	*scene, t_point	po, t_raycastor	*cast);

/* event_hook.c 2 okk*/
void	rotate(t_scene	*scene, double angl_turn);
void	translate(t_map	*tmap, double	mov);
int		key_hooks(int keycode, t_scene	*all);
void	hook_controls(t_scene	*scene);

/* event_hook_2.c */
void	floating_coord(t_map	*tmap, int	n_pix, int	sign);

/* cube_free.c 3*/
void	free_arr(char	***paths);
void	free_lst(t_lmap	**tokens);
int		close_cube3d(t_scene	*scene);

#endif