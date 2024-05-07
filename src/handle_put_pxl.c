/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_put_pxl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:11:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/07 19:13:09 by dklimkin         ###   ########.fr       */
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
	float	alpha;
	t_line	line;

	alpha = (1.0 * MINIMAP_FOV_LEN);
	line.current = (t_xy){round(params.start.x), round(params.start.y)};
	line.target = (t_xy){round(params.end.x), round(params.end.y)};
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
		alpha = fclamp((alpha - 0.10), 0, (1.0 * MINIMAP_FOV_LEN));
		put_pxl(img, (t_fxy){line.current.x, line.current.y}, create_color(
				(int)alpha, params.color.r, params.color.g, params.color.b));
		line.error_delta = (2 * line.error);
		if (step_the_line(&line, params) == FAILURE)
			break ;
	}
}

void	put_pxl(t_img img, t_fxy pos, unsigned int color)
{
	char	*pixel;
	float	alpha;
	t_rgb	rgb;
	int		x;
	int		y;

	x = (int)round(pos.x);
	y = (int)round(pos.y);
	if (x < 0 || y < 0 || x >= img.width || y >= img.height)
		return ;
	pixel = (char *)(img.addr + (y * img.line_len) + (x * (img.bpp / 8)));
	alpha = (color >> ALPHA_CH & 255) / 255.0;
	rgb.r = (int)(((1 - alpha) * ((*(int *)pixel >> RED_CH) & 255))
			+ (alpha * ((color >> RED_CH) & 255)));
	rgb.g = (int)((1 - alpha) * ((*(int *)pixel >> GREEN_CH) & 255)
			+ (alpha * ((color >> GREEN_CH) & 255)));
	rgb.b = (int)(((1 - alpha) * ((*(int *)pixel >> BLUE_CH) & 255))
			+ (alpha * ((color >> BLUE_CH) & 255)));
	*(int *)pixel = ((rgb.r << RED_CH) | (rgb.g << GREEN_CH) | rgb.b);
}
