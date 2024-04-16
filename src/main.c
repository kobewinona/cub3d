/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/16 23:03:05 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int testMap[MAP_WIDTH][MAP_HEIGHT] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int	game_exit(t_win *win, int exit_status)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (exit_status != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	exit(exit_status);
}

int	read_keys(int key_pressed, t_state **state)
{
	if (key_pressed == KEY_ESC)
		game_exit((*state)->win, EXIT_SUCCESS);
	if (key_pressed == KEY_W)
		(*state)->keys.move_up = true;
	if (key_pressed == KEY_S)
		(*state)->keys.move_down = true;
	if (key_pressed == KEY_A)
		(*state)->keys.move_left = true;
	if (key_pressed == KEY_D)
		(*state)->keys.move_right = true;
	if (key_pressed == LEFT_ARROW)
		(*state)->keys.turn_left = true;
	if (key_pressed == RIGHT_ARROW)
		(*state)->keys.turn_right = true;
	return (SUCCESS);
}

int	release_keys(int key, t_state **state)
{
	if (key == KEY_W)
		(*state)->keys.move_up = false;
	if (key == KEY_S)
		(*state)->keys.move_down = false;
	if (key == KEY_A)
		(*state)->keys.move_left = false;
	if (key == KEY_D)
		(*state)->keys.move_right = false;
	if (key == LEFT_ARROW)
		(*state)->keys.turn_left = false;
	if (key == RIGHT_ARROW)
		(*state)->keys.turn_right = false;

	return (SUCCESS);
}

void	turn_right(t_state *state)
{
	if (state->keys.turn_right)
	{
		if (state->vep_pos.x > 0 && state->vep_pos.x <= MAP_WIDTH)
			state->vep_pos.x += CAMERA_SPEED;
		else
		{
			if (state->vep_pos.y > 0 && state->vep_pos.y <= MAP_HEIGHT)
				state->vep_pos.y += CAMERA_SPEED;
		}
	}
}

void	update_visual_endpoint_position(t_state *state)
{
	if (state->p_dir.y != 0)
		state->vep_pos.y = state->p_dir.y < 0 ? 0 : MAP_HEIGHT;
	if (state->p_dir.x != 0)
		state->vep_pos.x = state->p_dir.x < 0 ? 0 : MAP_WIDTH;
	if (state->keys.turn_left && state->vep_pos.x > 0)
		state->vep_pos.x -= 0.05;
	if (state->keys.turn_right && state->vep_pos.x < MAP_WIDTH - 1)
		turn_right(state);
}

void	update_player_position(t_state *state)
{
	int		dir_x;
	int		dir_y;
	int		index_to_check_x;
	int		index_to_check_y;

	dir_x = (state->keys.move_right - state->keys.move_left);
	dir_y = (state->keys.move_down - state->keys.move_up);
	index_to_check_x = (int)round(state->p_pos.x);
	index_to_check_y = (int)round(state->p_pos.y);
	if (dir_x > 0)
		index_to_check_x = (int)floor(state->p_pos.x) + dir_x;
	if (dir_x < 0)
		index_to_check_x = (int)ceil(state->p_pos.x) + dir_x;
	if (dir_y > 0)
		index_to_check_y = (int)floor(state->p_pos.y) + dir_y;
	if (dir_y < 0)
		index_to_check_y = (int)ceil(state->p_pos.y) + dir_y;
	if (testMap[(int)floor(state->p_pos.y)][index_to_check_x] < 1)
	{
		if ((float)state->p_pos.y > (float)floor(state->p_pos.y))
		{
			if (testMap[(int)floor(state->p_pos.y) + 1][index_to_check_x] < 1)
				state->p_pos.x += (PLAYER_SPEED * dir_x);
		}
		else
			state->p_pos.x += (PLAYER_SPEED * dir_x);
	}
	else
		state->p_pos.x = (float)round(state->p_pos.x);
	if (testMap[index_to_check_y][(int)(state->p_pos.x)] < 1)
	{
		if ((float)state->p_pos.x > (float)floor(state->p_pos.x))
		{
			if (testMap[index_to_check_y][(int)floor(state->p_pos.x) + 1] < 1)
				state->p_pos.y += (PLAYER_SPEED * dir_y);
		}
		else
			state->p_pos.y += (PLAYER_SPEED * dir_y);
	}
	else
		state->p_pos.y = (float)round(state->p_pos.y);
}

void	render_layout(t_state *state)
{
	int	layout_color;
	int	y;
	int	x;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (testMap[y][x] >= 1)
				layout_color = create_color(200, 0, 0, 150);
			else
				layout_color = create_color(255, 25, 25, 25);
			draw_shape((t_shape){(t_xy){x * CELL_SIZE, y * CELL_SIZE},
				CELL_SIZE, CELL_SIZE, layout_color}, *(state->canvas));
			x++;
		}
		y++;
	}
}

int	render_game(t_state **state)
{
	update_player_position((*state));
	update_visual_endpoint_position((*state));
	// printf("state->vep_pos.y %f, state->vep_pos.x %f\n", (*state)->vep_pos.y, (*state)->vep_pos.x);
	render_layout((*state));
	draw_shape((t_shape){(t_xy){(*state)->p_pos.x * CELL_SIZE,
		(*state)->p_pos.y * CELL_SIZE}, CELL_SIZE, CELL_SIZE,
		create_color(200, 150, 0, 100)}, (*(*state)->canvas));
	draw_shape((t_shape){(t_xy){(*state)->vep_pos.x * CELL_SIZE,
		(*state)->vep_pos.y * CELL_SIZE}, CELL_SIZE, CELL_SIZE,
		create_color(150, 150, 0, 150)}, (*(*state)->canvas));
	mlx_put_image_to_window((*state)->win->mlx_ptr,
		(*state)->win->win_ptr, (*state)->canvas->img_ptr, 0, 0);
	return (SUCCESS);
}

int	main(void)
{
	t_state	*state;
	t_win	*win;

	print_map(testMap);
	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
		return (EXIT_FAILURE);
	ft_memset(state, 0, sizeof(t_state));
	state->p_pos = (t_xy){22, 19};
	state->p_dir = (t_xy){0, -1};
	state->vep_pos = (t_xy){22, 19};
	if (create_window(SCREEN_WIDTH, SCREEN_HEIGHT, &win) == FAILURE)
		return (EXIT_FAILURE);
	state->win = win;
	state->canvas = create_image(SCREEN_WIDTH, SCREEN_HEIGHT, state->win->mlx_ptr);
	mlx_loop_hook(win->mlx_ptr, render_game, &state);
	mlx_hook(win->win_ptr, 02, (1L << 0), read_keys, &state);
	mlx_hook(win->win_ptr, 03, (1L << 1), release_keys, &state);
	mlx_hook(win->win_ptr, 17, 0, game_exit, win);
	mlx_loop(win->mlx_ptr);
	return (game_exit(win, EXIT_SUCCESS));
}
