/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:04:03 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/16 19:43:21 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// @attention
# include <stdio.h>

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include "constants.h"

// @typedef structs

typedef struct s_xy
{
	double	x;
	double	y;
}	t_xy;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}	t_win;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_shape
{
	t_xy	pos;
	int		width;
	int		height;
	int		color;
}	t_shape;

typedef struct s_keys
{
	bool	move_up;
	bool	move_down;
	bool	move_left;
	bool	move_right;
	bool	turn_left;
	bool	turn_right;
}	t_keys;

typedef struct s_state
{
	t_win	*win;
	t_xy	p_pos;
	t_xy	vep_pos;
	t_xy	p_dir;
	t_keys	keys;
	t_img	*canvas;
}	t_state;

typedef enum s_argb
{
	BLUE_CH = 0,
	GREEN_CH = 8,
	RED_CH = 16,
	ALPHA_CH = 24,
}	t_argb;

// map utils
void	print_map(int map[MAP_WIDTH][MAP_HEIGHT]);
int		render_game(t_state **state);
void	render_layout(t_state *state);

// graphics utils
int		create_window(int w, int h, t_win **win);
t_img	*create_image(int width, int height, void *mlx_ptr);
void	put_pixel_img(t_img img, t_xy pos, int color);
void	draw_shape(t_shape shape, t_img img);
int		create_color(int alpha, int red, int green, int blue);

// colors utils
int		create_color(int alpha, int red, int green, int blue);
int		blend_colors(unsigned int bg_color, unsigned int fg_color);
int		get_argb_value(int argb, t_argb chanel);

#endif