# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: layang <layang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 15:21:57 by layang            #+#    #+#              #
#    Updated: 2025/06/07 14:26:22 by layang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d
CC = cc
CFLAGS = -Werror -Wall -Wextra -g

#CFLAGS_B = -Werror -Wall -Wextra -fsanitize=address -fPIC

RM = rm -rf

SRC_F = ./src/
SRC_C = main.c \
		minimap.c \
		cube_free.c \
		event_hook.c \
		cube_utils.c

SRCS = $(addprefix $(SRC_F), $(SRC_C))

LIBC =  -Llibft -Lminilibx-linux
LINKS = -lmlx -lft -lm -lpthread -lX11 -lXext

OBJS = $(SRCS:.c=.o)

CYAN = \033[0;36m
RESET = \033[0m

$(NAME) : $(OBJS)
	@echo ""
	@echo "${CYAN}Compiling libft and minilibx-linux...${RESET}"
	$(MAKE) bonus -C libft
	@echo ""
	$(MAKE) -C minilibx-linux
	@echo ""
	@echo "${CYAN}libft and minilibx-linux Created${RESET}"
	@echo ""
	@echo "${CYAN}Compiling $(NAME)...${RESET}"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBC) $(LINKS)
	@echo ""
	@echo "${CYAN}$(NAME) Created${RESET}"

all : $(NAME)

fclean : clean
	$(MAKE) fclean -C libft

clean :
	$(RM) $(NAME) $(OBJS)
	$(MAKE) clean -C libft

re : fclean all

bonus : $(NAME)

.PHONY: all bonus clean fclean re