/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:34:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/07 10:01:21 by tat-nguy         ###   ########.fr       */
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
	int		posx;
	int		posy;
	int		dirx;
	int		diry;
	t_count	count;
	
}	t_map;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/* parsing */

bool	is_cub_file(char *path);
char	**read_file(char *path);

int	is_texture_line(char *line);
int	is_color_line(char *line);
bool	is_empty_line(char *line);
bool	is_map_line(char *s);

int	ft_parsing(char *path, t_map *map);
void	parse_texture_line(char *line, t_map *map);
void	parse_color_line(char *line, t_map *map);
int	color_int(char *r, char *g, char *b);
void	parse_map_block(char **line, t_map *map);



int	print_error(char *str);
void	print_map(char **map);

void	free_map_data(t_map *map);


int	is_valid_map(char **map);
bool	is_bordered(char **map);

#endif