/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:32:53 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/18 17:36:22 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_layout(t_state *state)
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
			if (g_test_map[y][x] >= 1)
				layout_color = create_color(200, 0, 0, 150);
			else
				layout_color = create_color(255, 25, 25, 25);
			draw_square((t_square){(t_xy){x * CELL_SIZE, y * CELL_SIZE},
				CELL_SIZE, CELL_SIZE, layout_color}, *(state->canvas));
			x++;
		}
		y++;
	}
}

static void	draw_direction_vector(t_state *state, t_img *canvas)
{
	double	length;
	t_xy	end_point;

	length = 4;
	end_point = (t_xy){state->p_pos.x + state->p_dir.x * length,
		state->p_pos.y + state->p_dir.y * length};
	draw_line((t_line){{state->p_pos.x * CELL_SIZE, state->p_pos.y * CELL_SIZE},
	{end_point.x * CELL_SIZE, end_point.y * CELL_SIZE},
		create_color(255, 100, 0, 255)}, (*canvas), 0);
}

int	render_game(t_state **state)
{
	update_player_direction((*state));
	update_player_position((*state));
	printf("player direction x %lf, player direction y %lf\n",
		(*state)->p_dir.x, (*state)->p_dir.y);
	printf("plane x %lf, plane y %lf\n", (*state)->plane.x, (*state)->plane.y);
	render_layout((*state));
	draw_direction_vector(*state, (*state)->canvas);
	draw_square((t_square){(t_xy){((*state)->p_pos.x * CELL_SIZE)
		- (PLAYER_SIZE / 2), ((*state)->p_pos.y * CELL_SIZE)
		- (PLAYER_SIZE / 2)}, PLAYER_SIZE, PLAYER_SIZE,
		create_color(200, 150, 0, 100)}, (*(*state)->canvas));
	put_pixel_img((*(*state)->canvas), (t_xy){(*state)->p_pos.x
		* CELL_SIZE, (*state)->p_pos.y * CELL_SIZE},
		create_color(255, 255, 255, 255));
	handle_raycasting(state);
	mlx_put_image_to_window((*state)->win->mlx_ptr,
		(*state)->win->win_ptr, (*state)->canvas->img_ptr, 0, 0);
	return (SUCCESS);
}
