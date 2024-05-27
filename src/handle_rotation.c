/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:09:02 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/27 14:19:35 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_camera_speed(t_state *state)
{
	if (state->keys.turn_right || state->keys.turn_left)
		state->cam_speed = fclamp(state->cam_speed + 0.005, 0, CAMERA_SPEED);
	else
		state->cam_speed = CAMERA_SPEED / 4;
}

void	update_player_direction(t_state *state)
{
	float	old_dir_x;
	double	new_angle;

	update_camera_speed(state);
	old_dir_x = state->p_dir.x;
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
}
