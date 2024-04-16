/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:01:21 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 00:12:46 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <fcntl.h>
# include <stdbool.h>
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

/*
RETURN VALUE
- NORMAL RETURN
	0:	success
	-1:	allocation failed

- CAN'T FIND SOME ELEMENT
	1:	can't find north
	2:	can't find south
	4:	can't find west
	8:	can't find east
	16:	can't find floor
	32:	can't find ceil

- ELEMENT INFO ERROR
	2^8:	north file error
	2^9:	south file error
	2^10:	west file error
	2^11:	east file error
	2^12:	floor info is wrong
	2^13:	ceil info is wrong

- ELEMENT FIELD INPUT (too much or lack)
	2^16:	north input field must be 2
	2^17:	south input field must be 2
	2^18:	west input field must be 2
	2^19:	east input field must be 2
	2^20:	floor input field must be 2
	2^21:	ceil input field must be 2

- FINDING MAP TOO EARLY OR NOT FIND AT ALL
	2^24:	find map? too early (stop reading map)
	2^25:	map doesn't exist in this file (reach eof)
	2^26:	duplicate element
*/

// main function
int			par_open_cub3d(const char *path);
t_parser	parser_init(void *mlx);


// get element
int	par_get_element(t_parser *info, int fd, char **ext_buff);

// parser_utils
void	par_error_msg(char *msg);

#endif