/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 21:07:06 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_texture	*sb_get_ptr(t_parser *info, t_ltype type)
{
	t_texture	*ptr;

	ptr = NULL;
	if (type == north_elem)
		ptr = &info->north;
	else if (type == south_elem)
		ptr = &info->south;
	else if (type == west_elem)
		ptr = &info->west;
	else if (type == east_elem)
		ptr = &info->east;
	return (ptr);
}

int	par_get_texture(char **box, t_parser *info, t_ltype type)
{
	int			height;
	int			width;
	t_texture	*ptr;

	ptr = sb_get_ptr(info, type);
	ptr->img = mlx_xpm_file_to_image(info->mlx, box[1], &width, &height);
	if (ptr->img == NULL)
		return (1);
	ptr->width = width;
	ptr->height = height;
	return (0);
}
