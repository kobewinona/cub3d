/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:40:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/07 18:53:45 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_color(int alpha, int red, int green, int blue)
{
	if (alpha > 255 || red > 255 || green > 255 || blue > 255)
		return (0);
	return (alpha << ALPHA_CH | red << RED_CH | green << GREEN_CH | blue);
}

t_rgb	get_color_rgb(int color)
{
	return ((t_rgb){color >> RED_CH & 255,
		color >> GREEN_CH & 255, color & 255, true});
}

t_rgb	get_color_from_img(void *img_ptr, int x, int y)
{
	t_img			img;
	char			*addr;
	unsigned int	color;

	addr = mlx_get_data_addr(img_ptr, &img.bpp, &img.line_len, &img.endian);
	color = *(unsigned int *)(addr + (x * (img.bpp / 8)) + (y * img.line_len));
	return ((t_rgb){color >> RED_CH & 255,
		color >> GREEN_CH & 255, color & 255, true});
}
