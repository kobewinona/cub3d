/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:12:17 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 22:20:40 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_assign(t_parser *info, void *img, int area[], t_elem_type type)
{
	t_texture	*ptr_texture;
	
	if (type == north_elem)
		ptr_texture = &info->north;
	else if (type == south_elem)
		ptr_texture = &info->south;
	else if (type == west_elem)
		ptr_texture = &info->west;
	else if (type == east_elem)
		ptr_texture = &info->east;
	else
		return ;
	ptr_texture->img = img;
	ptr_texture->width = area[0];
	ptr_texture->height = area[1];
}

int	par_get_texture(t_parser *info, char **box, t_elem_type type)
{
	void			*img;
	int				area[2];
	t_error_type	err;

	err = no_error;
	if (ft_split_len(box) != 2)
		return (par_element_bitmask(type, args_error));
	img = mlx_xpm_file_to_image(info->mlx, box[1], &area[0], &area[1]);
	if (img == NULL)
		err = data_error;
	sb_assign(info, img, area, type);
	return (par_element_bitmask(type, err));
}