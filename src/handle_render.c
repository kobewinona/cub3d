/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:32:53 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/07 18:36:07 by dklimkin         ###   ########.fr       */
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
	free((*state)->rays);
	(*state)->rays = NULL;
	return (SUCCESS);
}
