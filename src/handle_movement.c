/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:33:27 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/27 19:00:01 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_direction(t_state *state)
{
	double	old_dir_x;
	double	old_plane_x;
	double	new_angle;

	if (state->keys.turn_right || state->keys.turn_left)
	{
		if (state->cam_speed > CAMERA_SPEED)
			state->cam_speed = CAMERA_SPEED;
		else
			state->cam_speed += 0.006;
	}
	else
		state->cam_speed = 0;
	old_dir_x = state->p_dir.x;
	old_plane_x = state->plane.x;
	new_angle = ((state->keys.turn_right - state->keys.turn_left)
			* state->cam_speed);
	state->p_dir_angle += (new_angle);
	while (state->p_dir_angle >= 2 * PI)
		state->p_dir_angle -= 2 * PI;
	while (state->p_dir_angle < 0)
		state->p_dir_angle += 2 * PI;
	state->p_dir.x = (state->p_dir.x * cos(new_angle))
		- (state->p_dir.y * sin(new_angle));
	state->p_dir.y = old_dir_x * sin(new_angle)
		+ state->p_dir.y * cos(new_angle);
	state->plane.x = state->plane.x * cos(new_angle)
		- state->plane.y * sin(new_angle);
	state->plane.y = old_plane_x * sin(new_angle)
		+ state->plane.y * cos(new_angle);
}

static void	calculate_screen_shaking(t_state *state, int dir_x, int dir_y)
{
	// printf("dir_x %d, dir_y %d\n", dir_x, dir_y);
	if (dir_x != 0 || dir_y != 0)
	{
		if (state->mov_offset > 4)
			state->mov_offset_step = -1;
		if (state->mov_offset < 0)
			state->mov_offset_step = 1;
		state->mov_offset += MOVEMENT_SHAKING * state->mov_offset_step;
	}
	else
	{
		if (state->mov_offset > 0)
			state->mov_offset -= (MOVEMENT_SHAKING * 3);
		else
			state->mov_offset = 0;
	}
}

void	update_player_position(t_state *state)
{
	double	next_pos_x;
	double	next_pos_y;
	int		dir_x;
	int		dir_y;
	float	player_speed;

	player_speed = PLAYER_SPEED;
	dir_x = (state->keys.move_left - state->keys.move_right);
	dir_y = (state->keys.move_forwards - state->keys.move_backwards);
	if (state->keys.move_forwards || state->keys.move_backwards)
	{
		if (state->keys.move_backwards)
			player_speed /= 2;
		next_pos_x = state->p_pos.x + ((player_speed * state->p_dir.x) * dir_y);
		next_pos_y = state->p_pos.y + ((player_speed * state->p_dir.y) * dir_y);
		if (g_test_map[(int)state->p_pos.y][(int)next_pos_x] < 1)
			state->p_pos.x = next_pos_x;
		if (g_test_map[(int)next_pos_y][(int)state->p_pos.x] < 1)
			state->p_pos.y = next_pos_y;
	}
	player_speed /= 1.5;
	if (state->keys.move_left || state->keys.move_right)
	{
		next_pos_x = state->p_pos.x + ((player_speed * state->p_dir.y) * dir_x);
		next_pos_y = state->p_pos.y - ((player_speed * state->p_dir.x) * dir_x);
		if (g_test_map[(int)state->p_pos.y][(int)next_pos_x] < 1)
			state->p_pos.x = next_pos_x;
		if (g_test_map[(int)next_pos_y][(int)state->p_pos.x] < 1)
			state->p_pos.y = next_pos_y;
	}
	calculate_screen_shaking(state, dir_x, dir_y);
}
