/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:33:27 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/24 20:19:42 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_direction(t_state *state)
{
	double	old_dir_x;
	double	old_plane_x;
	double	new_angle;

	old_dir_x = state->p_dir.x;
	old_plane_x = state->plane.x;
	new_angle = ((state->keys.turn_right - state->keys.turn_left)
			* CAMERA_SPEED);
	state->p_dir_angle += ((state->keys.turn_left - state->keys.turn_right)
			* CAMERA_SPEED);
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
	printf("state->p_dir_angle %lf\n", state->p_dir_angle);
}

void	update_player_position(t_state *state)
{
	double	next_pos_x;
	double	next_pos_y;
	int		dir_x;
	int		dir_y;

	dir_x = (state->keys.move_left - state->keys.move_right);
	dir_y = (state->keys.move_up - state->keys.move_down);
	if (state->keys.move_up || state->keys.move_down)
	{
		next_pos_x = state->p_pos.x + ((PLAYER_SPEED * state->p_dir.x) * dir_y);
		next_pos_y = state->p_pos.y + ((PLAYER_SPEED * state->p_dir.y) * dir_y);
		if (g_test_map[(int)state->p_pos.y][(int)next_pos_x] < 1)
			state->p_pos.x = next_pos_x;
		if (g_test_map[(int)next_pos_y][(int)state->p_pos.x] < 1)
			state->p_pos.y = next_pos_y;
	}
	if (state->keys.move_left || state->keys.move_right)
	{
		next_pos_x = state->p_pos.x + ((PLAYER_SPEED * state->p_dir.y) * dir_x);
		next_pos_y = state->p_pos.y - ((PLAYER_SPEED * state->p_dir.x) * dir_x);
		if (g_test_map[(int)state->p_pos.y][(int)next_pos_x] < 1)
			state->p_pos.x = next_pos_x;
		if (g_test_map[(int)next_pos_y][(int)state->p_pos.x] < 1)
			state->p_pos.y = next_pos_y;
	}
}
