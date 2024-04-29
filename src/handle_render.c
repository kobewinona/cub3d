/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:32:53 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/29 21:00:26 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_minimap(t_state *state, t_minimap *minimap)
{
	minimap->opacity = clamp(MINIMAP_OPACITY, 0, 255);
	minimap->bg_color = create_color(minimap->opacity, 20, 20, 20);
	minimap->player_color = create_color(minimap->opacity, 120, 120, 180);
	minimap->wall_color = create_color(minimap->opacity, 90, 100, 105);
	minimap->pos = (t_fxy){SCREEN_WIDTH - MINIMAP_WIDTH + MINIMAP_X, MINIMAP_Y};
	minimap->start_pos = (t_xy){
		(int)state->p_pos.x - (MINIMAP_WIDTH / 2 / MINIMAP_CELL_SIZE),
		(int)state->p_pos.y - (MINIMAP_HEIGHT / 2 / MINIMAP_CELL_SIZE)};
	minimap->offset.x = MINIMAP_WIDTH - (MINIMAP_WIDTH / 2);
	minimap->offset.y = MINIMAP_HEIGHT - (MINIMAP_HEIGHT / 2);
	minimap->center_pos.x = minimap->pos.x
		+ (MINIMAP_WIDTH / 2) + MINIMAP_CELL_SIZE / 2;
	minimap->center_pos.y = minimap->pos.y
		+ (MINIMAP_HEIGHT / 2) + MINIMAP_CELL_SIZE / 2;
}

static void	render_minimap_layout_row(t_minimap minimap, int y, t_img canvas)
{
	int	map_x;
	int	map_y;
	int	x;

	x = 0;
	while (x < MINIMAP_WIDTH / MINIMAP_CELL_SIZE)
	{
		map_x = minimap.start_pos.x + x;
		map_y = minimap.start_pos.y + y;
		if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT)
		{
			if (g_test_map[map_y][map_x] > 0)
			{
				draw_square((t_square){{minimap.pos.x + x * MINIMAP_CELL_SIZE,
					minimap.pos.y + y * MINIMAP_CELL_SIZE},
					MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE,
					minimap.wall_color}, canvas);
			}
		}
		x++;
	}
}

static void	render_field_of_view(t_state *state, t_minimap minimap, t_fxy *rays)
{
	t_fxy	ray_end_pos;
	int		i;

	i = 0;
	while (i < (SCREEN_WIDTH - 1))
	{
		ray_end_pos.x = minimap.pos.x + (rays[i].x - minimap.start_pos.x)
			* MINIMAP_CELL_SIZE;
		ray_end_pos.y = minimap.pos.y + (rays[i].y - minimap.start_pos.y)
			* MINIMAP_CELL_SIZE;
		draw_line((t_line){{minimap.p_pos.x, minimap.p_pos.y},
		{ray_end_pos.x, ray_end_pos.y},
			create_color(255, 200, 50, 100)}, (*state->canvas), 0);
		i++;
	}
	draw_square((t_square){{minimap.p_pos.x - (MINIMAP_CELL_SIZE / 2),
		minimap.p_pos.y - (MINIMAP_CELL_SIZE / 2)},
		MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE,
		minimap.player_color}, (*state->canvas));
	put_pixel_img((*state->canvas), (t_fxy){minimap.p_pos.x, minimap.p_pos.y},
		create_color(255, 200, 200, 200));
	free(state->rays);
}

void	render_minimap(t_state *state)
{
	t_minimap	minimap;
	int			map_y;
	t_fxy		ray_end_pos;
	t_fxy		p_pos;
	int			y;

	init_minimap(state, &minimap);
	draw_square((t_square){{minimap.pos.x, minimap.pos.y},
		MINIMAP_WIDTH, MINIMAP_HEIGHT, minimap.bg_color}, (*state->canvas));
	y = 0;
	while (y < MINIMAP_HEIGHT / MINIMAP_CELL_SIZE)
	{
		render_minimap_layout_row(minimap, y, (*state->canvas));
		y++;
	}
	minimap.p_pos.x = minimap.pos.x + (state->p_pos.x - minimap.start_pos.x)
		* MINIMAP_CELL_SIZE;
	minimap.p_pos.y = minimap.pos.y + (state->p_pos.y - minimap.start_pos.y)
		* MINIMAP_CELL_SIZE;
	render_field_of_view(state, minimap, state->rays);
}

int	render_game(t_state **state)
{
	update_player_direction((*state));
	update_player_position((*state));
	handle_raycasting(state);
	render_minimap((*state));
	mlx_put_image_to_window((*state)->win->mlx_ptr,
		(*state)->win->win_ptr, (*state)->canvas->img_ptr, 0, 0);
	return (SUCCESS);
}
