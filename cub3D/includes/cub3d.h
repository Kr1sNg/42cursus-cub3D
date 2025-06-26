/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:34:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/26 15:33:16 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"
// # include "../minilibx/mlx_int.h"
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
# define MAX_HITS_PER_RAY 20
# define DOOR_CLOSED 0
# define DOOR_OPENING 1
# define DOOR_OPEN 2
# define DOOR_CLOSING 3

// # define WIDTH			1920
// # define HEIGHT			1080
# define WIDTH			920
# define HEIGHT			680

# define WHITE			0xFFFFFF
# define BLACK			0x000000
# define PURPLE			0x9400D3

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

typedef enum e_hit
{
	DEFAULT = -1,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR,
	SPRITE
}	t_hit;

typedef struct s_point
{
	int		x;
	int		y;
	int		color;
}	t_point;

typedef struct s_pic
{
	void	*mlx_img;
	void	*addr;
	int		bits_pix;
	int		line_len;
	int		endian;
	int		width;
	int		height;
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
	int		animation;
	// move here for parsing
	int		map_posx; // horizontal
	int		map_posy; //  vertical
	double	map_dirx; // N=(dirx = 0, diry = -1), S=(dirx = 0, diry = 1)
	double	map_diry; // W=(dirx = -1, diry = 0), E=(dirx = 1, diry = 0)
}	t_count;

//	double	inv_det;
typedef struct s_sprite
{
	double	dx;
	double	dy;
	double	tx;
	double	ty;
	int		sprix;
	int		sprih;
	int		spriw;
	t_point	ds;
	t_point	de;
}	t_sprite;

typedef struct s_ray_hit
{
	t_hit	hit_type;
	t_hit	hit_dir;
	double	dist;
	t_point	hit_map;//t_point	in_map;
	int		vert_side;
	double	hit_x;
	double	hit_y;
	double	tex_x;
	t_pic	tt_pic;
}	t_ray_hit;

typedef struct s_ray
{
	t_ray_hit	hits[MAX_HITS_PER_RAY];
	int			hit_count;
}	t_ray;

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
	t_pic	tt_pic;
	int		this_r;
	t_point	p;
	double	dis_h;
	double	dis_v;
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
	t_hit	vhit_dir;
	t_hit	hhit_dir;
	t_hit	hit_dir;
	t_point	offset;
	t_point	in_map;
}	t_raycastor;

typedef struct s_cam
{
	int			posx; // horizontal
	int			posy; //  vertical
	double		dirx; // N=(dirx = 0, diry = -1), S=(dirx = 0, diry = 1)
	double		diry; // W=(dirx = -1, diry = 0), E=(dirx = 1, diry = 0)
	t_raycastor	*ray2;
	double		zbuffer[WIDTH];
	t_point		sprites[MAX_HITS_PER_RAY];
	int			nb_sprites;
	double		planex;
	double		planey;
	double		p_angle;
	double		pitch;
	double		fov;
	int			ray_nb;	
}	t_cam;

typedef struct s_map
{
	t_pic	door; //2
	//t_pic	door_open; //2
	t_pic	sprite; //3
	t_pic	tex_n;
	t_pic	tex_s;
	t_pic	tex_w;
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
	t_count	count;
	int		visible;
	int		sprite_on;
	int		**door_state;
	double	**door_timer;
	int		*order;
}	t_map;

typedef struct s_scene
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
void	free_map_img(t_scene *scene);
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

/*main */
// animation
bool	animated_sprit(void *mlx, t_map *tmap);
bool	check_img(void *mlx, t_pic *image, char *path);

/* draw_3d.c  ok*/
void	draw_3d_scene(t_scene *scene, t_point p, int grid);

/*draw_minimap.c 5 ok*/
void	line_bh(t_scene	*scene, t_point	s, t_point	e, t_raycastor	*cast);
void	draw_player_vision(t_scene *scene, t_point p, int grid, t_point	off);

/* draw_maps.c 4 */
void	draw_maps(t_scene	*scene);

/* minimap_utils.c 5 ok*/
int		inside_map_array(int x, int y, t_scene *scene);
void	draw_square(t_scene	*scene, t_point p, int size);
void	draw_player_vector(t_scene *scene, t_point player, int len);
double	dist(double sx, double sy, double ex, double ey);
void	init_raycastor(t_point p, t_raycastor	*cast);

/* raycast.c  ok*/
void	intersect_v(t_raycastor	*cast, t_point p, int *depth);
void	get_dis_v(t_raycastor	*cast, t_scene *scene, t_point p, int *depth);
void	intersect_h(t_raycastor	*cast, t_point p, int *depth);
void	get_dis_h(t_raycastor	*cast, t_scene *scene, t_point p, int *depth);

/*raycast_utils.c ok*/
void	no_wall(t_scene *scene, t_raycastor	*cast, int *depth);
int		hit_wall(t_map	*tmap, t_point p, int is_3d);
void	renew_pos_in_map(t_scene *scene, t_raycastor	*cast);
t_hit	find_hit_side(t_raycastor	*cast, char c, int is_dir, int is_v);

/*raycast_3d.c  ok*/
void	renew_hits(t_raycastor	*cast, t_scene	*s, t_ray	*hitps, char c);
void	record_hits(t_raycastor	*cast, t_scene	*sc, t_ray	*hitps, char c);
void	get_hit_v(t_raycastor	*cast, t_scene	*sc,
			int	*depth, t_ray	*hs);
void	get_hit_h(t_raycastor	*cast, t_scene	*sc,
			int	*depth, t_ray	*hs);

/*raycast_3d_utils.c 4 */
void	get_correct_dist(t_raycastor	*cast);
void	get_render_height(t_raycastor	*cast, t_scene *scene,
			t_ray_hit	hit);
int		have_repeat(t_point in, t_ray	*hitps, double dist);
t_pic	find_texture_3d(t_scene	*scene, t_ray_hit	hit);

/*draw_3d_utils.c OK*/
void	draw_wall_column(t_raycastor	*cast, t_scene *scene,
			t_ray_hit	hit);
void	draw_door_height(t_raycastor	*cast, t_scene *scene,
			t_ray_hit	hit);
void	clear_zbuffer_sprites(t_cam *player);
void	sort_hit_points(t_ray	*hitps, t_scene *scene);

/* doors.c  OK*/
int		init_doors(t_map	*tmap);
void	update_doors(t_map	*tmap);

/*draw_sprite.c ok*/
void	put_col_sprite(t_sprite	spt, t_pic	sprt, t_scene	*sc, t_point	*c);
void	sort_draw_sprites(t_scene *scene, t_point p);

/* cube_utils.c ok*/
int		gradient_color(float_t	r, int s, int e);
double	normalize_angle(double angle);
double	get_player_angle(t_map *tmap);
void	put_pixel(t_pic	*img, t_point	pt);
double	sp_dist(t_cam *player, t_point	po, t_point	s, int n);

/*draw_textures.c ok*/
int		get_color_at(t_pic *img, int x, int y);
double	get_texture_x(t_raycastor	*cast, t_ray_hit	hit);
//t_pic	find_texture_xpm(t_scene *scene, t_raycastor *cast);
void	put_pixel_texture(t_scene *scene, t_point po, t_raycastor *cast);
void	texture_3d(t_scene	*scene, t_point	po, t_raycastor	*cast,
			t_ray_hit	hit);

/* event_hook.c 2 ok*/
void	rotate(t_scene	*scene, double angl_turn);
// void	translate(t_map	*tmap, double mov);
int		key_hooks(int keycode, t_scene	*all);
int		mouse_rotate(t_scene *all);
void	hook_controls(t_scene	*scene);

/* event_hook_2.c */
void	floating_coord(t_map *tmap, int n_pix, int sign);

/* cube_free.c 3*/
void	free_arr(void ***paths);
int		close_cube3d(t_scene *scene);

#endif