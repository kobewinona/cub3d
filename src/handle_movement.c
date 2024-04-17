/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:33:27 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/17 22:26:00 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void update_player_direction(t_state *state)
{
	double rotSpeed = 0.05; // Adjust rotation speed here
	if (state->keys.turn_left)
	{
		double oldDirX = state->p_dir.x;
		state->p_dir.x = state->p_dir.x * cos(rotSpeed) - state->p_dir.y * sin(rotSpeed);
		state->p_dir.y = oldDirX * sin(rotSpeed) + state->p_dir.y * cos(rotSpeed);
	}
	if (state->keys.turn_right)
	{
		double oldDirX = state->p_dir.x;
		state->p_dir.x = state->p_dir.x * cos(-rotSpeed) - state->p_dir.y * sin(-rotSpeed);
		state->p_dir.y = oldDirX * sin(-rotSpeed) + state->p_dir.y * cos(-rotSpeed);
	}
}

void	update_player_position(t_state *state)
{
	int		dir_x;
	int		dir_y;
	double	next_pos_x;
	double	next_pos_y;

	dir_x = (int)(state->keys.move_right - state->keys.move_left);
	dir_y = (int)(state->keys.move_down - state->keys.move_up);
	next_pos_x = state->p_pos.x + (PLAYER_SPEED * dir_x);
	next_pos_y = state->p_pos.y + (PLAYER_SPEED * dir_y);
	if (testMap[(int)state->p_pos.y][(int)next_pos_x] < 1)
		state->p_pos.x = next_pos_x;
	if (testMap[(int)next_pos_y][(int)state->p_pos.x] < 1)
		state->p_pos.y = next_pos_y;
}
