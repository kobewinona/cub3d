/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:04:03 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/17 22:28:11 by dklimkin         ###   ########.fr       */
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

extern int	testMap[MAP_WIDTH][MAP_HEIGHT];

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

typedef struct s_square
{
	t_xy	pos;
	int		width;
	int		height;
	int		color;
}	t_square;

typedef struct s_line
{
	t_xy	start;
	t_xy	end;
	int		color;

}	t_line;

typedef struct s_line_calc
{
	int	current_x;
	int	current_y;
	int	target_x;
	int	target_y;
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
	int	error;
	int	error_delta;
}	t_line_calc;

typedef struct s_keys
{
	bool	move_up;
	bool	move_down;
	bool	move_left;
	bool	move_right;
	bool	turn_left;
	bool	turn_right;
}	t_keys;

typedef struct s_vep
{
	t_xy	pos;
	double	angle;
}	t_vep;

typedef struct s_state
{
	t_win	*win;
	t_xy	p_pos;
	t_xy	p_dir;
	t_xy	plane;
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

int		game_exit(t_win *win, int exit_status);

// render
int		render_game(t_state **state);

// raycasting
void	handle_raycasting(t_state **state);

// input
int		read_keys(int key_pressed, t_state **state);
int		release_keys(int key, t_state **state);

// player
void	update_player_position(t_state *state);
void	update_player_direction(t_state *state);

// map utils
void	print_map(int map[MAP_WIDTH][MAP_HEIGHT]);

// graphics utils
int		create_window(int w, int h, t_win **win);
t_img	*create_image(int width, int height, void *mlx_ptr);
void	put_pixel_img(t_img img, t_xy pos, int color);
int		create_color(int alpha, int red, int green, int blue);
void	draw_square(t_square params, t_img img);
void	draw_line(t_line params, t_img img, int side);

// colors utils
int		create_color(int alpha, int red, int green, int blue);
int		blend_colors(unsigned int bg_color, unsigned int fg_color);
int		get_argb_value(int argb, t_argb chanel);

#endif