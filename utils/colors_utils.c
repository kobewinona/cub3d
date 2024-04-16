/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:40:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/16 15:52:07 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_color(int alpha, int red, int green, int blue)
{
	if (alpha > 255 || red > 255 || green > 255 || blue > 255)
		return (0);
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

int	blend_colors(unsigned int bg_color, unsigned int fg_color)
{
	float	alpha;
	int		red;
	int		green;
	int		blue;

	alpha = (fg_color >> 24) / 255.0;
	red = (int)((1 - alpha)
			* get_argb_value(bg_color, RED_CH) + alpha
			* get_argb_value(fg_color, RED_CH));
	green = (int)((1 - alpha)
			* get_argb_value(bg_color, GREEN_CH) + alpha
			* get_argb_value(fg_color, GREEN_CH));
	blue = (int)((1 - alpha)
			* get_argb_value(bg_color, BLUE_CH) + alpha
			* get_argb_value(fg_color, BLUE_CH));
	return ((red << 16) | (green << 8) | blue);
}

int	get_argb_value(int argb, t_argb chanel)
{
	return ((argb >> chanel) & 0xFF);
}
