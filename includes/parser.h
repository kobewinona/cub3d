/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:01:21 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/15 14:25:19 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <fcntl.h>
# include <stdbool.h>
# include "constants.h"
# include "../libs/libft/includes/libft.h"

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
int		par_open_cub3d(const char *path);
t_parser	parser_init(void *mlx);


// get element
int	par_get_element(t_parser *info, int fd, char **ext_buff);

// parser_utils
void	par_error_msg(char *msg);

#endif