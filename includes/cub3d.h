/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:04:03 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/12 16:04:10 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// @attention
# include <stdio.h>

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include "constants.h"

// @typedef structs

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}	t_win;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_xy
{
	int	x;
	int	y;
}	t_xy;

// map utils
void	print_map(int map[MAP_WIDTH][MAP_HEIGHT]);

// graphics utils
int		create_window(int w, int h, t_win **win);
t_img	*create_image(int width, int height, void *mlx_ptr);
void	put_pixel_img(t_img img, t_xy pos, int color);
int		create_color(int alpha, int red, int green, int blue);

#endif