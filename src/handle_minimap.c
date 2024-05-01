/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:04:04 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/01 20:43:12 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	calculate_fov_radius(float *len, int i)
// {
// 	float	len_step;
// 	float	max_len;
// 	int		mid_point;
// 	float	angle;

// 	len_step = max_len / mid_point;
// 	max_len = 5.0;
// 	mid_point = SCREEN_WIDTH / 2;
// 	angle = (float)i / (SCREEN_WIDTH - 1) * PI;
// 	(*len) = max_len * sin(angle);
// }

static void	render_player_fov(t_state *state, t_minimap minimap, t_fxy *rays)
{
	t_fxy	ray_end_pos;
	int		i;

	i = 0;
	while (rays[i].x && rays[i].y && i < (SCREEN_WIDTH - 1))
	{
		ray_end_pos.x = minimap.pos.x + (rays[i].x - minimap.start_pos.x)
			* MINIMAP_CELL_SIZE;
		ray_end_pos.y = minimap.pos.y + (rays[i].y - minimap.start_pos.y)
			* MINIMAP_CELL_SIZE;
		put_line((t_line_params){minimap.p_pos, ray_end_pos, (t_bounds){
			MINIMAP_Y, minimap.pos.x + MINIMAP_WIDTH,
			MINIMAP_Y + MINIMAP_HEIGHT, minimap.pos.x},
			create_color(5, 80, 120, 100), INT_MAX}, (*state->canvas));
		i++;
	}
	put_square((t_square){{minimap.p_pos.x - (MINIMAP_CELL_SIZE / 2),
		minimap.p_pos.y - (MINIMAP_CELL_SIZE / 2)},
		MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE,
		minimap.player_color}, (*state->canvas));
	put_pxl((*state->canvas), (t_fxy){minimap.p_pos.x, minimap.p_pos.y},
		create_color(255, 50, 150, 10));
	free(state->rays);
}

static void	render_minimap_scnaline(t_state *state, t_minimap minimap, int y)
{
	int	map_x;
	int	map_y;
	int	width;
	int	height;
	int	x;

	width = state->info.width;
	height = state->info.height;
	x = 0;
	while (x < MINIMAP_WIDTH / MINIMAP_CELL_SIZE)
	{
		map_x = minimap.start_pos.x + x;
		map_y = minimap.start_pos.y + y;
		if (map_x >= 0 && map_x < width && map_y >= 0 && map_y < height)
		{
			if (state->info.map[map_y][map_x] == 1)
			{
				put_square((t_square){{minimap.pos.x + x * MINIMAP_CELL_SIZE,
					minimap.pos.y + y * MINIMAP_CELL_SIZE},
					MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE,
					minimap.wall_color}, (*state->canvas));
			}
		}
		x++;
	}
}

static void	set_minimap_data(t_state *state, t_minimap *minimap)
{
	minimap->opacity = clamp(MINIMAP_OPACITY, 0, 255);
	minimap->bg_color = create_color(minimap->opacity, 20, 20, 20);
	minimap->player_color = create_color(minimap->opacity, 20, 60, 5);
	minimap->wall_color = create_color(minimap->opacity - 100, 120, 170, 100);
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

void	render_minimap(t_state *state)
{
	t_minimap	minimap;
	int			map_y;
	t_fxy		ray_end_pos;
	t_fxy		p_pos;
	int			y;

	set_minimap_data(state, &minimap);
	put_square((t_square){{minimap.pos.x, minimap.pos.y},
		MINIMAP_WIDTH, MINIMAP_HEIGHT, minimap.bg_color}, (*state->canvas));
	y = 0;
	while (y < MINIMAP_HEIGHT / MINIMAP_CELL_SIZE)
		render_minimap_scnaline(state, minimap, y++);
	minimap.p_pos.x = minimap.pos.x + (state->p_pos.x - minimap.start_pos.x)
		* MINIMAP_CELL_SIZE;
	minimap.p_pos.y = minimap.pos.y + (state->p_pos.y - minimap.start_pos.y)
		* MINIMAP_CELL_SIZE;
	render_player_fov(state, minimap, state->rays);
}
