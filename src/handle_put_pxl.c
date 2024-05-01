/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_put_pxl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:11:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/01 20:36:28 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_square(t_square params, t_img img)
{
	int	y;
	int	x;

	y = 0;
	while (y < params.height && (y + params.pos.y) < img.height)
	{
		x = 0;
		while (x < params.width && (x + params.pos.x) < img.width)
		{
			put_pxl(img,
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
	if (line->current.x == params.bounds.left)
		return (FAILURE);
	if (line->current.x == params.bounds.right)
		return (FAILURE);
	if (line->current.y == params.bounds.top)
		return (FAILURE);
	if (line->current.y == params.bounds.bottom)
		return (FAILURE);
	return (SUCCESS);
}

void	put_line(t_line_params params, t_img img)
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
		put_pxl(img, (t_fxy){line.current.x, line.current.y}, params.color);
		line.error_delta = (2 * line.error);
		if (step_the_line(&line, params) == FAILURE)
			break ;
	}
}

static int	blend_colors(unsigned int bg_color, unsigned int fg_color)
{
	float	alpha;
	int		red;
	int		green;
	int		blue;

	alpha = (fg_color >> ALPHA_CH) / 255.0;
	red = (int)((1 - alpha)
			* ((bg_color >> RED_CH) & 0xFF) + alpha
			* ((fg_color >> RED_CH) & 0xFF));
	green = (int)((1 - alpha)
			* ((bg_color >> GREEN_CH) & 0xFF) + alpha
			* ((fg_color >> GREEN_CH) & 0xFF));
	blue = (int)((1 - alpha)
			* ((bg_color >> BLUE_CH) & 0xFF) + alpha
			* ((fg_color >> BLUE_CH) & 0xFF));
	return ((red << RED_CH) | (green << GREEN_CH) | blue);
}

void	put_pxl(t_img img, t_fxy pos, int color)
{
	int		offset;
	char	*pixel;
	int		y;
	int		x;

	y = (int)round(pos.y);
	x = (int)round(pos.x);
	if (x < 0 || y < 0 || x >= img.width || y >= img.height)
		return ;
	offset = (y * img.line_len) + (x * (img.bpp / 8));
	pixel = (char *)(img.addr + offset);
	*(int *)pixel = blend_colors(*(int *)pixel, color);
}
