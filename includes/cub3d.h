/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:04:03 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/29 21:31:45 by dklimkin         ###   ########.fr       */
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
# include <limits.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include "constants.h"

extern int	g_test_map[MAP_WIDTH][MAP_HEIGHT];

// @typedef structs

typedef struct s_keys
{
	bool	move_forwards;
	bool	move_backwards;
	bool	move_left;
	bool	move_right;
	bool	turn_left;
	bool	turn_right;
}	t_keys;

typedef struct s_fxy
{
	float	x;
	float	y;
}	t_fxy;

typedef struct s_xy
{
	int	x;
	int	y;
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
	t_fxy	pos;
	int		width;
	int		height;
	int		color;
}	t_square;

typedef struct s_line
{
	t_fxy	start;
	t_fxy	end;
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

typedef struct s_ray
{
	float	angle;
	t_fxy	dir;
	t_fxy	delta_dist;
	float	perp_dist;
	t_fxy	side_dist;
	t_xy	map;
	t_xy	step;
	bool	is_obstacle_hit;
	bool	is_back_side;
}	t_ray;

typedef struct s_shadow
{
	int	max_opacity;
	int	opacity;
	int	factor;
	int	color;
}	t_shadow;

typedef struct s_column
{
	int			height;
	int			wall_start;
	int			wall_end;
	int			ceil_color;
	int			floor_color;
	t_shadow	shadow;
}	t_column;

typedef struct s_minimap
{
	int		bg_color;
	int		player_color;
	int		wall_color;
	int		opacity;
	t_fxy	pos;
	t_fxy	p_pos;
	t_fxy	center_pos;
	t_fxy	offset;
	t_xy	start_pos;
}	t_minimap;

typedef struct s_state
{
	t_win	*win;
	t_fxy	p_pos;
	t_fxy	p_dir;
	float	p_dir_angle;
	t_fxy	plane;
	t_keys	keys;
	t_img	*canvas;
	int		log_fd;
	float	mov_offset;
	int		mov_offset_step;
	float	mov_speed;
	float	cam_speed;
	t_fxy	*rays;
}	t_state;

typedef enum s_argb
{
	BLUE_CH = 0,
	GREEN_CH = 8,
	RED_CH = 16,
	ALPHA_CH = 24,
}	t_argb;

int		game_exit(t_state **state, int exit_status);

// render
int		render_game(t_state **state);

// raycasting
void	handle_raycasting(t_state **state);

// input
int		read_keys_pressed(int key_pressed, t_state **state);
int		read_keys_released(int key, t_state **state);

// player
void	update_player_position(t_state *state);
void	update_player_direction(t_state *state);

// map utils
void	print_map(int map[MAP_WIDTH][MAP_HEIGHT]);

// graphics utils
int		create_window(int w, int h, t_win **win);
t_img	*create_image(int width, int height, void *mlx_ptr);
void	put_pixel_img(t_img img, t_fxy pos, int color);
int		create_color(int alpha, int red, int green, int blue);
int		blend_colors(unsigned int bg_color, unsigned int fg_color);
void	draw_square(t_square params, t_img img);
void	draw_line(t_line params, t_img img, int side);
void	draw_column(t_state *state, t_ray ray, int x);

// clamp
int		clamp(int value, int min, int max);
float	fclamp(float value, float min, float max);

#endif