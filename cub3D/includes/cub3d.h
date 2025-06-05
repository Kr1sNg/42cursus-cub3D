/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:34:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/05 12:01:45 by tat-nguy         ###   ########.fr       */
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

typedef struct s_map
{
	void	*tex_n;
	void	*tex_s;
	void	*tex_w;
	void	*tex_e;
	int		color_f;
	int		color_c;
	char	**map;
	int		posx;
	int		posy;
	int		dirx;
	int		diry;
	
}	t_map;


typedef struct s_texture
{
	int		count_no;
	int		count_so;
	int		count_we;
	int		count_ea;
}	t_texture;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/* parsing */

bool	is_cub_file(char *path);
char	**read_file(char *path);

bool	is_texture_line(char *line);
bool	is_color_line(char *line);
bool	is_empty_line(char *line);
bool	is_map_line(char *s);

int	ft_parsing(char *path, t_map *map);
int	parse_texture_line(char *line, t_map *map);
int	parse_color_line(char *line, t_map *map);

int	print_error(char *str);
#endif