/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_put_scanline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:59:55 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/01 20:40:36 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw(t_state *state, t_ray ray, t_scanline scanline, int x)
{
	t_rgb	color;
	int		y;

	y = 0;
	while (y < scanline.wall_start)
	{
		put_pxl((*state->canvas), (t_fxy){x, y},
			create_color(255, state->info.ceil.r,
				state->info.ceil.g, state->info.ceil.b));
		y++;
	}
	int i = 0;
	while (y < scanline.wall_end)
	{
		color = get_color_from_img(state->info.south.img, 0, clamp(i, 0, 50));
		i++;
		put_pxl((*state->canvas), (t_fxy){x, y},
			create_color(255, color.r, color.g, color.b));
		// put_pxl((*state->canvas), (t_fxy){x, y},
		// 	create_color(255, 5, 70, 120));
		scanline.shadow.color = create_color(scanline.shadow.opacity, 0, 0, 0);
		put_pxl((*state->canvas), (t_fxy){x, y}, scanline.shadow.color);
		y++;
	}
	while (y < (SCREEN_HEIGHT - 1))
	{
		put_pxl((*state->canvas), (t_fxy){x, y},
			create_color(255, state->info.floor.r,
				state->info.floor.g, state->info.floor.b));
		y++;
	}
}

static void	set_scanline_data(t_state *state, t_ray ray, t_scanline *scanline)
{
	t_shadow	shadow;
	float		exponent;

	scanline->height = (int)(SCREEN_WIDTH / (ray.perp_dist * cos(ray.angle)));
	scanline->wall_start = -scanline->height / 2 + SCREEN_HEIGHT / 2;
	if (scanline->wall_start < 0)
		scanline->wall_start = 0;
	scanline->wall_start += (int)state->mov_offset * 5;
	scanline->wall_end = scanline->height / 2 + SCREEN_HEIGHT / 2;
	if (scanline->wall_end >= SCREEN_HEIGHT)
		scanline->wall_end = SCREEN_HEIGHT - 1;
	scanline->wall_end += (int)state->mov_offset * 5;
	shadow.max_opacity = 200;
	shadow.factor = 10;
	if (ray.is_back_side)
		shadow.factor = 5;
	exponent = (1 - exp(-(ray.perp_dist / shadow.factor)));
	shadow.opacity = (shadow.max_opacity * exponent);
	if (shadow.opacity > shadow.max_opacity)
		shadow.opacity = shadow.max_opacity;
	scanline->shadow = shadow;
}

void	put_scanline(t_state *state, t_ray ray, int x)
{
	t_scanline	scanline;

	set_scanline_data(state, ray, &scanline);
	draw(state, ray, scanline, x);
}
