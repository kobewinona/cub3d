/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/01 18:16:14 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	parser_free(t_parser *info, int *fd, char **ext_buff)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
	if (ext_buff != NULL)
	{
		free(*ext_buff);
		*ext_buff = NULL;
	}
	if (info->north.img != NULL)
		mlx_destroy_image(info->mlx, info->north.img);
	if (info->south.img != NULL)
		mlx_destroy_image(info->mlx, info->south.img);
	if (info->east.img != NULL)
		mlx_destroy_image(info->mlx, info->east.img);
	if (info->west.img != NULL)
		mlx_destroy_image(info->mlx, info->west.img);
	if (info->mlx != NULL)
		free(info->mlx);
	ft_free_split(info->map);
}


// going to toilet elsewhere