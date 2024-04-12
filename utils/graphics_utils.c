/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:17:25 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/12 18:14:12 by dklimkin         ###   ########.fr       */
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

t_img	*create_image(int w, int h, void *mlx_ptr)
{
	t_img	*img;

	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img_ptr = mlx_new_image(mlx_ptr, w, h);
	if (!img->img_ptr)
		return (NULL);
	img->addr = mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->line_len, &img->endian);
	img->width = w;
	img->height = w;
	return (img);
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

