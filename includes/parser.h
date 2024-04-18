/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:01:21 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/18 16:58:50 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <fcntl.h>
# include <stdbool.h>
# include <sys/errno.h>
# include "constants.h"
# include "ft_queue.h"
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"

typedef enum e_elem_type
{
	north_elem = 1,
	south_elem = 2,
	east_elem = 3,
	west_elem = 4,
	floor_elem = 5,
	ceil_elem = 6
}	t_elem_type;

typedef enum e_elem_error
{
	not_found = 0,
	data_error = 8,
	args_error = 16,
	no_error = 32
}	t_error_type;

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
}	t_texture;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	bool			isinit;
}	t_rgb;

typedef enum e_direction
{
	undefine,
	north,
	south,
	west,
	east
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
	char		**map;
	int			width;
	int			height;
	t_player	player;
}	t_parser;

// main function
int			par_open_cub3d(const char *path);
t_parser	parser_init(void *mlx);

// get element
char		*par_read_element(t_queue *element, int fd, char **ext_buff);

// parser_utils
void		par_error_msg(char *msg);

bool		par_ismap(char *line);
bool		par_isspace(char *line);

#endif