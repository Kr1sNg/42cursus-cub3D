# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 19:03:06 by tat-nguy          #+#    #+#              #
#    Updated: 2025/06/10 18:08:33 by tat-nguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Libft
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# MLX
MLX_DIR		= ./minilibx
MLX			= $(MLX_DIR)/libmlx.a

# Source Files
SRC_DIR 	= src
SUBDIRS		= main parsing scene
SRC_SUBDIR	= $(foreach dir, $(SUBDIRS), $(addprefix $(SRC_DIR)/, $(dir)))
SRC     	= $(foreach dir, $(SRC_SUBDIR), $(wildcard $(dir)/*.c))

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

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(INCLUDE) $(CFLAGS) $(LIBFLAGS) $(MLXFLAGS) -lm

# Clean
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

bonus: re

.PHONY: all clean fclean re bonus

