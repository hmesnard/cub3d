# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/15 14:08:28 by hmesnard          #+#    #+#              #
#    Updated: 2021/04/22 11:36:22 by hmesnard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS_COMMON	=	get_cub.c \
				get_cub_valid_line.c \
				get_cub_value.c \
				get_cub_utils.c \
				split_map.c \
				valid_map.c \
				init_data.c \
				make_bmp.c \
				error_free.c \
				utils.c \
				get_next_line.c \
				get_next_line_utils.c

SRCS_MAND	=	main.c \
				hooks.c \
				move_turn.c \
				raycasting.c \
				raycasting_sprites.c \

SRCS_BONUS	=	main_bonus.c \
				hooks_bonus.c \
				move_turn_bonus.c\
				raycasting_bonus.c \
				raycasting_sprites_bonus.c \
				bonus.c

OBJS_COMMON	=	$(SRCS_COMMON:.c=.o)

OBJS_MAND	=	$(SRCS_MAND:.c=.o)

OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

MLX			=	-lmlx -framework OpenGL -framework AppKit

RM			=	rm -rf

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS_COMMON) $(OBJS_MAND)
			$(CC) $(MLX) libmlx.a -o $@ $^
			$(RM) $(OBJS_BONUS)

all:		$(NAME)

bonus:		$(OBJS_COMMON) $(OBJS_BONUS)
			$(CC) $(MLX) libmlx.a -o $(NAME) $^
			$(RM) $(OBJS_MAND)
			touch bonus

clean:
			$(RM) $(OBJS_COMMON) $(OBJS_MAND) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME) bonus

re:			fclean all

.PHONY:		all clean fclean re
