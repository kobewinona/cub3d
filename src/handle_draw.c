/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:11:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/01 00:44:22 by dklimkin         ###   ########.fr       */
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

static int	step_the_line(t_line *line, t_line_params params)
{
	if (line->error_delta >= line->delta.y)
	{
		line->error += line->delta.y;
		line->current.x += line->step.x;
	}
	if (line->error_delta <= line->delta.x)
	{
		line->error += line->delta.x;
		line->current.y += line->step.y;
	}
	line->len++;
	if (line->len >= params.len)
		return (FAILURE);
	if (line->current.x == params.max_x0 || line->current.x == params.max_x1)
		return (FAILURE);
	if (line->current.y == params.max_y0 || line->current.y == params.max_y1)
		return (FAILURE);
	return (SUCCESS);
}

void	draw_line(t_line_params params, t_img img)
{
	t_line	line;

	line = (t_line){round(params.start.x), round(params.start.y),
		round(params.end.x), round(params.end.y)};
	line.len = 0;
	line.delta.x = abs(line.target.x - line.current.x);
	line.delta.y = -abs(line.target.y - line.current.y);
	line.step.x = -1;
	if (line.current.x < line.target.x)
		line.step.x = 1;
	line.step.y = -1;
	if (line.current.y < line.target.y)
		line.step.y = 1;
	line.error = (line.delta.x + line.delta.y);
	while (line.current.x != line.target.x || line.current.y != line.target.y)
	{
		put_pixel_img(img, (t_fxy){line.current.x,
			line.current.y}, params.color);
		line.error_delta = (2 * line.error);
		if (step_the_line(&line, params) == FAILURE)
			break ;
	}
}

static void	draw(t_state *state, t_ray ray, t_column column, int x)
{
	int	y;

	y = 0;
	while (y < column.wall_start)
	{
		put_pixel_img((*state->canvas), (t_fxy){x, y},
			create_color(255, state->info.ceil.r,
				state->info.ceil.g, state->info.ceil.b));
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
			create_color(255, state->info.floor.r,
				state->info.floor.g, state->info.floor.b));
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
