/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:01:21 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 21:33:45 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/errno.h>
# include "constants.h"
# include "ft_queue.h"
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
}	t_texture;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
	bool	isinit;
}	t_rgb;

typedef enum e_direction
{
	no_player,
	north,
	south,
	west,
	east,
	too_many_player
}	t_direction;

typedef struct s_player
{
	int			x;
	int			y;
	t_direction	face;
}	t_player;

typedef struct s_parser
{
	void		*mlx;
	void		*window;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	t_rgb		floor;
	t_rgb		ceil;
	int			init_checker;
	char		**map;
	size_t		width;
	size_t		height;
	t_player	player;
}	t_parser;

// cub file function
int		par_open_cub3d(const char *path);
int		par_read_cub3d(int fd, t_queue *map);

// function wrapper
void	parser_job(int fd, t_parser *info);

// initialize & free function
int		parser_init(t_parser *info);
void	parser_free(t_parser *info);

// debugger
void	par_print_map(t_parser *info);
bool	par_elem_error(t_parser *info, t_queue *map, t_queue *elem, t_queue *e);
bool	parser_debug(t_parser *info, bool isprint);

// element extract
int		par_get_texture(char **box, t_parser *info, t_ltype type);
int		par_get_color(char **box, t_parser *info, t_ltype type);
int		par_get_element(t_parser *info, t_queue *element, t_queue *err);

// filter
void	par_filter(t_queue *map, t_queue *element);

// get element
t_node	*par_read_element(t_queue *element, int fd, char **ext_buff, int *bit);

// parser_utils
void	par_error_msg(char *msg);
bool	par_ismap(char *line);
bool	par_isspace(char *line);
bool	par_isplayer(char c);
int		par_set_element_bits(int bit, int *bits, t_ltype *type, t_ltype t1);

// Map handler
char	**par_get_map(t_queue *map_queue, t_parser *info);
int		par_read_map(t_queue *maps, t_parser *info);
void	par_find_player_by_line(char *line, size_t line_no, t_player *player);
bool	par_floodfill(t_parser *info);

#endif