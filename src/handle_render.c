/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:32:53 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/01 20:04:18 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_game(t_state **state)
{
	update_player_direction((*state));
	update_player_position((*state));
	handle_raycasting(state);
	render_minimap((*state));
	mlx_put_image_to_window((*state)->info.mlx,
		(*state)->win->win_ptr, (*state)->canvas->img_ptr, 0, 0);
	mlx_put_image_to_window((*state)->info.mlx,
		(*state)->win->win_ptr, (*state)->info.south.img, 0, 0);
	return (SUCCESS);
}
