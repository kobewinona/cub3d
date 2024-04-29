/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:33:27 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/29 13:09:41 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_screen_shaking(t_state *state, int dir_x, int dir_y)
{
	float	movement_shaking;

	movement_shaking = (3 * state->mov_speed);
	if (dir_x != 0 || dir_y != 0)
	{
		if (state->mov_offset > 3)
			state->mov_offset_step = -1;
		if (state->mov_offset < 0)
			state->mov_offset_step = 1;
		state->mov_offset += movement_shaking * state->mov_offset_step;
	}
	else
	{
		if (state->mov_offset > 0)
			state->mov_offset -= (movement_shaking * 3);
		else
			state->mov_offset = 0;
	}
}

static void	handle_sideways_movement(t_state *state, int dir_x)
{
	t_xy	next_pos;
	int		next_map_pos_x;
	int		next_map_pos_y;
	float	player_speed;

	state->mov_speed = (PLAYER_SPEED / 1.5);
	next_pos.x = state->p_pos.x + ((state->mov_speed * state->p_dir.y) * dir_x);
	next_map_pos_x = clamp((int)next_pos.x, 0, (MAP_WIDTH - 1));
	next_pos.y = state->p_pos.y - ((state->mov_speed * state->p_dir.x) * dir_x);
	next_map_pos_y = clamp((int)next_pos.y, 0, (MAP_HEIGHT - 1));
	if (g_test_map[(int)state->p_pos.y][next_map_pos_x] < 1)
		state->p_pos.x = next_pos.x;
	if (g_test_map[next_map_pos_y][(int)state->p_pos.x] < 1)
		state->p_pos.y = next_pos.y;
}

static void	handle_forward_movement(t_state *state, int dir_y)
{
	t_xy	next_pos;
	int		next_map_pos_x;
	int		next_map_pos_y;
	float	player_speed;

	state->mov_speed = PLAYER_SPEED;
	if (state->keys.move_left || state->keys.move_right)
		state->mov_speed = (PLAYER_SPEED / 1.5);
	if (state->keys.move_backwards)
		state->mov_speed /= 2;
	next_pos.x = state->p_pos.x + ((state->mov_speed * state->p_dir.x) * dir_y);
	next_map_pos_x = clamp((int)next_pos.x, 0, (MAP_WIDTH - 1));
	next_pos.y = state->p_pos.y + ((state->mov_speed * state->p_dir.y) * dir_y);
	next_map_pos_y = clamp((int)next_pos.y, 0, (MAP_HEIGHT - 1));
	if (g_test_map[(int)state->p_pos.y][next_map_pos_x] < 1)
		state->p_pos.x = next_pos.x;
	if (g_test_map[next_map_pos_y][(int)state->p_pos.x] < 1)
		state->p_pos.y = next_pos.y;
}

void	update_player_position(t_state *state)
{
	int		dir_x;
	int		dir_y;
	float	player_speed;

	dir_x = (state->keys.move_left - state->keys.move_right);
	dir_y = (state->keys.move_forwards - state->keys.move_backwards);
	if (state->keys.move_forwards || state->keys.move_backwards)
		handle_forward_movement(state, dir_y);
	if (state->keys.move_left || state->keys.move_right)
		handle_sideways_movement(state, dir_x);
	calculate_screen_shaking(state, dir_x, dir_y);
}
