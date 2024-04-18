/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:36:26 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/18 18:44:10 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_keys_pressed(int key_pressed, t_state **state)
{
	if (key_pressed == KEY_ESC)
		game_exit(state, EXIT_SUCCESS);
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

int	read_keys_released(int key_released, t_state **state)
{
	if (key_released == KEY_W)
		(*state)->keys.move_up = false;
	if (key_released == KEY_S)
		(*state)->keys.move_down = false;
	if (key_released == KEY_A)
		(*state)->keys.move_left = false;
	if (key_released == KEY_D)
		(*state)->keys.move_right = false;
	if (key_released == LEFT_ARROW)
		(*state)->keys.turn_left = false;
	if (key_released == RIGHT_ARROW)
		(*state)->keys.turn_right = false;
	return (SUCCESS);
}
