/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:11:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/18 17:33:37 by dklimkin         ###   ########.fr       */
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
				(t_xy){x + params.pos.x, y + params.pos.y}, params.color);
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
		put_pixel_img(img, (t_xy){lc.current_x, lc.current_y}, params.color);
		if (lc.current_x == lc.target_x && lc.current_y == lc.target_y)
			break ;
		lc.error_delta = (2 * lc.error);
		handle_delta_error(&lc);
	}
}
