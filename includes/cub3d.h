/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:04:03 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/24 19:51:37 by dklimkin         ###   ########.fr       */
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
# include <float.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include "constants.h"

extern int	g_test_map[MAP_WIDTH][MAP_HEIGHT];

// @typedef structs

typedef struct s_keys
{
	bool	move_up;
	bool	move_down;
	bool	move_left;
	bool	move_right;
	bool	turn_left;
	bool	turn_right;
}	t_keys;

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

// typedef struct s_raycast_calc
// {
// 	double	camera_x;
// 	double	ray_dir_x;
// 	double	ray_dir_y;
// 	double	side_dist_x;
// 	double	side_dist_y;
// 	double	delta_dist_x;
// 	double	delta_dist_y;
// 	int		step_x;
// 	int		step_y;
// 	int		map_x;
// 	int		map_y;
// 	bool	is_obstacle_hit;
// 	bool	is_obstacle_side;
// }	t_raycast_calc;

// delta_dist.x 1.5151515151515151
// delta_dist.y 1

typedef struct s_raycast_calc
{
	t_xy	ray_dir;
	t_xy	ray_start_pos;
	t_xy	ray_end_pos;
	t_xy	ray_dist;
	t_xy	delta_dist;
	t_xy	delta;
	t_xy	side_dist;
	t_xy	side_pos;
	t_xy	chande_in_pos;
	int		step_x;
	int		step_y;
	t_xy	map;
	t_xy	map_side;
	int		map_x;
	int		map_y;
	bool	is_obstacle_hit;
	bool	is_unit_side_x_hit;
	bool	is_unit_side_y_hit;
	bool	is_obstacle_side;
}	t_raycast_calc;

typedef struct s_state
{
	t_win	*win;
	t_xy	p_pos;
	t_xy	p_dir;
	double	p_dir_angle;
	t_xy	plane;
	t_keys	keys;
	t_img	*canvas;
	int		log_fd;
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
void	put_pixel_img(t_img img, t_xy pos, int color);
int		create_color(int alpha, int red, int green, int blue);
int		blend_colors(unsigned int bg_color, unsigned int fg_color);
void	draw_square(t_square params, t_img img);
void	draw_line(t_line params, t_img img, int side);

#endif