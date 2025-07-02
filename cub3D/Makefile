# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 19:03:06 by tat-nguy          #+#    #+#              #
#    Updated: 2025/07/02 08:46:25 by tat-nguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ***** Color Definition ***** #

RED 	= \033[91m
YELLOW 	= \033[33m
GREEN 	= \033[92m
RESET 	= \033[0m

# **************************** #

NAME = cub3D

# Libft
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# MLX
MLX_DIR		= ./minilibx
MLX			= $(MLX_DIR)/libmlx.a

# Source Files
SRC     	= src/main/animation.c src/main/main.c \
				src/parsing/error_map.c \
				src/parsing/free_map.c \
				src/parsing/is_line.c \
				src/parsing/map_floodfill.c \
				src/parsing/map_player.c \
				src/parsing/parse_lines.c \
				src/parsing/parse_map.c \
				src/parsing/parsing.c \
				src/parsing/read_file.c \
				src/parsing/utils.c \
				src/rendering/cube_free.c	 \
				src/rendering/cube_utils.c	 \
				src/rendering/doors.c	 \
				src/rendering/draw_3d.c	 \
				src/rendering/draw_3d_utils.c	 \
				src/rendering/draw_maps.c	 \
				src/rendering/draw_minimap.c	 \
				src/rendering/draw_sprite.c	 \
				src/rendering/draw_textures.c	 \
				src/rendering/event_hook.c	 \
				src/rendering/event_hook_2.c	 \
				src/rendering/minimap_utils.c	 \
				src/rendering/raycast.c	 \
				src/rendering/raycast_3d.c	 \
				src/rendering/raycast_3d_utils.c	 \
				src/rendering/raycast_utils.c	 \
				
# Object Files
OBJS 		= $(SRC:.c=.o)

# Include and Flags
INCLUDE 	= -Iincludes -Iminilibx
CFLAGS 		= -Wall -Wextra -Werror -I/usr/X11/include -g
CC 			= cc
RM			= rm -rf
LIBFLAGS	= -L$(LIBFT_DIR) -lft
MLXFLAGS	= -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lX11 -lXext

# Target
all: $(LIBFT) $(MLX) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW) 🛠️  waiting for compilation...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(INCLUDE) $(CFLAGS) $(LIBFLAGS) $(MLXFLAGS) -lm
	@echo "$(GREEN) 🤖  Compiled successful ✴️  $(NAME) ✴️$(RESET)"
	
# Clean
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "$(RED) 🗑️  Deleted object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(RED) 🚽  Deleted ❄️  $(NAME) ❄️$(RESET)"

re: fclean all

bonus: re

.PHONY: all clean fclean re bonus

