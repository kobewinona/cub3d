/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:44:39 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/15 21:14:33 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/*
RETURN VALUE (for bit mask)
0: success
-1: failure
*/

int	par_get_image(t_parser *info, char **box, size_t len, t_direction direct)
{
	t_texture	tmp;
	void		*mlx;
	int			width;
	int			height;

	mlx = info->mlx;
	tmp.img = mlx_xpm_file_to_image(mlx, box[1], &width, &height);
	tmp.width = width;
	tmp.height = height;
	if (direct == north)
		info->north = tmp;
	else if (direct == south)
		info->south = tmp;
	else if (direct == west)
		info->west = tmp;
	else if (direct == east)
		info->east = tmp;
}