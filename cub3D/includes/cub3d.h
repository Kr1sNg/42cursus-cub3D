/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:34:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/10 15:06:09 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MAX_LINES 1024

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

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

typedef struct s_count
{
	int		no_line;
	int		so_line;
	int		we_line;
	int		ea_line;
	int		f_line;
	int		c_line;
	int		map_lines;
	int		map_width; // include space
	int		player_count;
}	t_count;

typedef struct s_map
{
	void	*tex_n; //need to free
	void	*tex_s; //need to free
	void	*tex_w; //need to free
	void	*tex_e; //need to free
	int		color_f;
	int		color_c;
	char	**the_map;
	int		posx; // horizontal
	int		posy; //  vertical
	int		dirx; // N=(dirx = 0, diry = -1), S=(dirx = 0, diry = 1)
	int		diry; // W=(dirx = -1, diry = 0), E=(dirx = 1, diry = 0)
	char	**map_copy;
	t_count	count;
}	t_map;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/* parsing */
// error_map
void	perror_and_exit(t_map *map, char *str);
// free_map
void	free_map_data(t_map *map);
//is_line
int		is_texture_line(char *line);
int		is_color_line(char *line);
bool	is_empty_line(char *line);
bool	is_map_line(char *s);

//floodfill
bool	is_closed_map(t_map	*map, char **lines);

// player
bool	has_located_player(t_map *map);

//pars_lines
void	parse_texture_line(t_map *map, char **lines, int i);
void	parse_color_line(t_map *map, char **lines, int i);

//parse_map
int		parse_map_block(t_map *map, char **lines);
int		is_valid_map(t_map *map, char **lines);

// parsing
int		ft_parsing(char *path, t_map *map);

//read_file
bool	is_cub_file(char *path);
char	**read_file(char *path);

//utils
int		color_toi(t_map *map, char **split, char **lines);
void	print_map(t_map *map);

#endif