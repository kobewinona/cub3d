/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:17:25 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/17 22:03:22 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_window(void *mlx_ptr, int w, int h, t_win **win)
{
	(*win) = (t_win *)malloc(sizeof(t_win));
	if (!(*win))
		return (FAILURE);
	(*win)->win_ptr = mlx_new_window(mlx_ptr, w, h, TITLE);
	if (!(*win)->win_ptr)
		return (FAILURE);
	(*win)->width = w;
	(*win)->height = h;
	return (SUCCESS);
}

t_img	*create_image(void *mlx_ptr, int w, int h)
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
