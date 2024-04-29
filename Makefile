.PHONY:			all clean fclean re

MACHINE 		:= $(shell uname -m)
NAME			= cub3d

CC				= gcc
# CFLAGS			= -g -Wall -Wextra -Werror -MMD -03
CFLAGS			= -g -MMD #-O3
GFLAGS			= -lXext -lX11 -lm -lz
RM				= rm -rf

INCLUDES		= ./includes
SRCS_DIR		= ./src
OBJS_DIR		= ./obj
UTILS_DIR		= ./utils

LIBS_DIR		= ./libs
LIBFT_DIR		= $(LIBS_DIR)/libft
MINILIBX_DIR	= $(LIBS_DIR)/minilibx-linux
LIBFT			= $(LIBFT_DIR)/libft-$(MACHINE).a
MINILIBX		= $(MINILIBX_DIR)/libmlx_Linux.a

rwildcard		= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRCS			= $(call rwildcard, $(SRCS_DIR)/, *.c) $(call rwildcard, $(UTILS_DIR)/, *.c)
OBJS 			= $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS 			= $(OBJS:.o=.d)
LIBS			= -L$(LIBFT_DIR) $(MINILIBX) -L$(MINILIBX_DIR) $(LIBFT)

$(NAME): $(OBJS) Makefile
	@echo "Linking..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(GFLAGS) -o $(NAME)
	@echo "Build complete."

all: minilibx libft $(NAME)
	@echo "Building $(NAME)..."
	
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

-include $(DEPS)

libft:
	$(MAKE) -C $(LIBFT_DIR)

minilibx:
	$(MAKE) -C $(MINILIBX_DIR)

clean:
	$(RM) $(OBJS_DIR) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)

re: fclean all