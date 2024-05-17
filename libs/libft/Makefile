.PHONY:		all clean fclean re

NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

INCLUDES	= ./includes
SRCS_DIR	= ./src
CHECK_DIR	= $(SRCS_DIR)/check
CONVERT_DIR	= $(SRCS_DIR)/convert
GNL_DIR		= $(SRCS_DIR)/gnl
LIST_DIR	= $(SRCS_DIR)/list
MEMORY_DIR	= $(SRCS_DIR)/memory
PUT_DIR		= $(SRCS_DIR)/put
STRING_DIR	= $(SRCS_DIR)/string
OBJS_DIR	= ./obj

SRCS		= $(addprefix $(CHECK_DIR)/, \
				ft_isalpha.c ft_isascii.c ft_isdigit.c \
				ft_isextascii.c ft_isprint.c ft_isspace.c)
SRCS		+= $(addprefix $(CONVERT_DIR)/, \
				ft_atoi.c ft_atol.c ft_itoa.c)
SRCS		+= $(addprefix $(GNL_DIR)/, \
				get_next_line.c get_next_line_ext_buff.c)
SRCS		+= $(addprefix $(LIST_DIR)/, \
				ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
				ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
				ft_lstmap.c ft_lstnew.c ft_lstsize.c)
SRCS		+= $(addprefix $(MEMORY_DIR)/, \
				ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c \
				ft_memcpy.c ft_memmove.c ft_memset.c ft_realloc.c)
SRCS		+= $(addprefix $(PUT_DIR)/, \
				ft_putchar_fd.c ft_putendl_fd.c ft_putlstr_fd.c \
				ft_putnbr_fd.c ft_putstr_fd.c)
SRCS		+= $(addprefix $(STRING_DIR)/, \
				ft_free_split.c ft_split_len.c ft_strclen.c \
				ft_striteri.c ft_strlcat.c ft_strlen.c ft_strncmp.c \
				ft_strnstr.c ft_strtok.c ft_substr.c ft_toupper.c \
				ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
				ft_strlcpy.c ft_strmapi.c ft_strndup.c ft_strrchr.c \
				ft_strtrim.c ft_tolower.c)
OBJS 		= $(SRCS:%.c=$(OBJS_DIR)/%.o)

$(NAME): $(OBJS)
	$(AR) rcs $(NAME) $^

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all