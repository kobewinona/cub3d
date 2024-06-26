# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 22:55:43 by tponutha          #+#    #+#              #
#    Updated: 2024/05/28 21:36:49 by tponutha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Properties
NAME			= cub3d

# Compiler Flags
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g
GFLAGS			= -lXext -lX11 -lm -lz
RM				= rm -rf
NORM			= norminette -R CheckSourceForbiddenHeader

# Code Directories
INCLUDES		= ./includes
SRCS_DIR		= ./src
OBJS_DIR		= ./obj
LIBS_DIR		= ./libs

# Libraries Properties
LIBFT_DIR		= $(LIBS_DIR)/libft
MINILIBX_DIR	= $(LIBS_DIR)/minilibx-linux
LIBFT			= $(LIBFT_DIR)/libft.a
MINILIBX		= $(MINILIBX_DIR)/libmlx_Linux.a

# Libraries Flag
LIBFT_FLAG		= -L$(LIBFT_DIR) -lft
MINILIBX_FLAG	= -L$(MINILIBX_DIR) -lmlx_Linux
LIBSFLAG		= $(LIBFT_FLAG) $(MINILIBX_FLAG)

# Header files
HEADER			= constants.h cub3d.h ft_queue.h parser.h
HEADERS			= $(addprefix $(INCLUDES)/, $(HEADER))

# Source Codes
#	Main Code
MAIN_DIR		= $(SRCS_DIR)
MAIN_SRC		= main.c
MAIN_SRCS		= $(addprefix $(MAIN_DIR)/, $(MAIN_SRC))

#	Parser Code
PARSER_DIR		= $(SRCS_DIR)/parser
PARSER_SRC		= element_error.c get_color.c get_element.c \
					get_player.c get_texture.c map_floodfill.c \
					get_map.c open_cub3d.c parser_debug.c \
					parser_free.c parser_init.c parser_utils.c parser.c \
					print_map.c read_cub3d.c read_map.c
PARSER_SRCS		= $(addprefix $(PARSER_DIR)/, $(PARSER_SRC))

#	Queue Code
QUEUE_DIR		= $(SRCS_DIR)/queue
QUEUE_SRC		= node_delete.c node_new.c queue_dequeue.c \
					queue_flush.c queue_init.c queue_len.c queue_queue.c
QUEUE_SRCS		= $(addprefix $(QUEUE_DIR)/, $(QUEUE_SRC))

#	Render Code
RENDER_DIR		= $(SRCS_DIR)
RENDER_SRC		= handle_input.c handle_minimap.c handle_movement.c \
					handle_put_pxl.c handle_put_scanline.c \
					handle_raycasting.c handle_render.c handle_rotation.c
RENDER_SRCS		= $(addprefix $(RENDER_DIR)/, $(RENDER_SRC))

# Utils Code
UTILS_DIR		= ./utils
UTILS_SRC		= clamp.c colors_utils.c graphics_utils.c
UTILS_SRCS		= $(addprefix $(UTILS_DIR)/, $(UTILS_SRC))

# Source Code & Object Management
SRCS			= $(MAIN_SRCS) $(PARSER_SRCS) $(QUEUE_SRCS) $(RENDER_SRCS) $(UTILS_SRCS)
OBJS 			= $(SRCS:%.c=$(OBJS_DIR)/%.o)

# Main Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBSFLAG) $(GFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: %.c Makefile $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

# Make rule for libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Make rule for minilibx
$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) -C $(MINILIBX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(OBJS_DIR)
	$(RM) $(NAME)

re: fclean all

# For checking norm (except minilibx)
norm:
	$(NORM) $(LIBFT_DIR) $(SRCS) $(HEADERS)

.PHONY:	all clean fclean re norm
