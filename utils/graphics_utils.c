/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:17:25 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/29 12:41:26 by dklimkin         ###   ########.fr       */
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
	img->height = h;
	return (img);
}

void	put_pixel_img(t_img img, t_xy pos, int color)
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
	// printf("pixel %s\n", pixel);
	pixel = (char *)(img.addr + offset);
	*(int *)pixel = blend_colors(*(int *)pixel, color);
}
