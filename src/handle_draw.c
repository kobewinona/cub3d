/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:11:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/29 15:26:16 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_square params, t_img img)
{
	int	y;
	int	x;

	y = 0;
	while (y < params.height && (y + params.pos.y) < img.height)
	{
		x = 0;
		while (x < params.width && (x + params.pos.x) < img.width)
		{
			put_pixel_img(img,
				(t_fxy){x + params.pos.x, y + params.pos.y}, params.color);
			x++;
		}
		y++;
	}
}

static void	handle_delta_error(t_line_calc *lc)
{
	if (lc->error_delta >= lc->delta_y)
	{
		lc->error += lc->delta_y;
		lc->current_x += lc->step_x;
	}
	if (lc->error_delta <= lc->delta_x)
	{
		lc->error += lc->delta_x;
		lc->current_y += lc->step_y;
	}
}

void	draw_line(t_line params, t_img img, int side)
{
	t_line_calc	lc;

	lc = (t_line_calc){round(params.start.x), round(params.start.y),
		round(params.end.x), round(params.end.y)};
	lc.delta_x = abs(lc.target_x - lc.current_x);
	lc.delta_y = -abs(lc.target_y - lc.current_y);
	lc.step_x = -1;
	if (lc.current_x < lc.target_x)
		lc.step_x = 1;
	lc.step_y = -1;
	if (lc.current_y < lc.target_y)
		lc.step_y = 1;
	lc.error = (lc.delta_x + lc.delta_y);
	while (true)
	{
		put_pixel_img(img, (t_fxy){lc.current_x, lc.current_y}, params.color);
		if (lc.current_x == lc.target_x && lc.current_y == lc.target_y)
			break ;
		lc.error_delta = (2 * lc.error);
		handle_delta_error(&lc);
	}
}

static void	draw(t_state *state, t_ray ray, t_column column, int x)
{
	int	y;

	y = 0;
	while (y < column.wall_start)
	{
		put_pixel_img((*state->canvas), (t_fxy){x, y},
			create_color(255, 0, 0, 0));
		y++;
	}
	while (y < column.wall_end)
	{
		put_pixel_img((*state->canvas), (t_fxy){x, y},
			create_color(255, 5, 70, 120));
		column.shadow.color = create_color(column.shadow.opacity, 0, 0, 0);
		put_pixel_img((*state->canvas), (t_fxy){x, y}, column.shadow.color);
		y++;
	}
	while (y < (SCREEN_HEIGHT - 1))
	{
		put_pixel_img((*state->canvas), (t_fxy){x, y},
			create_color(255, 0, 0, 0));
		y++;
	}
}

void	draw_column(t_state *state, t_ray ray, int x)
{
	t_column	column;
	t_shadow	shadow;
	float		exponent;

	column.height = (int)(SCREEN_WIDTH / (ray.perp_dist * cos(ray.angle)));
	column.wall_start = -column.height / 2 + SCREEN_HEIGHT / 2;
	if (column.wall_start < 0)
		column.wall_start = 0;
	column.wall_start -= (int)state->mov_offset * 5;
	column.wall_end = column.height / 2 + SCREEN_HEIGHT / 2;
	if (column.wall_end >= SCREEN_HEIGHT)
		column.wall_end = SCREEN_HEIGHT - 1;
	column.wall_end -= (int)state->mov_offset * 5;
	shadow.max_opacity = 200;
	shadow.factor = 10;
	if (ray.is_back_side)
		shadow.factor = 5;
	exponent = (1 - exp(-(ray.perp_dist / shadow.factor)));
	shadow.opacity = (shadow.max_opacity * exponent);
	if (shadow.opacity > shadow.max_opacity)
		shadow.opacity = shadow.max_opacity;
	column.shadow = shadow;
	draw(state, ray, column, x);
}
