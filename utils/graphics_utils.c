/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:17:25 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/12 15:25:30 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_window(int w, int h, t_win **win)
{
	(*win) = (t_win *)malloc(sizeof(t_win));
	if (!(*win))
		return (FAILURE);
	(*win)->mlx_ptr = mlx_init();
	(*win)->win_ptr = mlx_new_window((*win)->mlx_ptr, w, h, TITLE);
	if (!(*win)->mlx_ptr || !(*win)->win_ptr)
		return (FAILURE);
	(*win)->width = w;
	(*win)->height = h;
	return (SUCCESS);
}

t_img	*create_image(int width, int height, void *mlx_ptr)
{
	t_img	*image;

	image = (t_img *)malloc(sizeof(t_img));
	if (!image)
		return (NULL);
	image->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!image->img_ptr)
		return (NULL);
	image->addr = mlx_get_data_addr(
			image->img_ptr, &image->bpp,
			&image->line_len, &image->endian);
	image->width = width;
	image->height = height;
	return (image);
}

void	put_pixel_img(t_img img, t_xy pos, int color)
{
	char	*dst;

	if ((pos.x >= 0 && pos.y >= 0) && (pos.x < img.width && pos.y < img.height))
	{
		dst = img.addr + ((pos.y * img.line_len) + (pos.x * (img.bpp / 8)));
		*(unsigned int *)dst = color;
	}
}

int	create_color(int alpha, int red, int green, int blue)
{
	if (alpha > 255 || red > 255 || green > 255 || blue > 255)
		return (0);
	alpha = 255 - alpha;
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

