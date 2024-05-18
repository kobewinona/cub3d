/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/18 21:57:18 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_check_null(int *fd, char **ext_buff)
{
	if (fd != NULL)
	{
		if (*fd >= 0)
			close(*fd);
		*fd = -1;
	}
	if (ext_buff != NULL)
	{
		free(*ext_buff);
		*ext_buff = NULL;
	}
}

void	parser_free(t_parser *info, int *fd, char **ext_buff)
{
	sb_check_null(fd, ext_buff);
	if (info->north.img != NULL)
		mlx_destroy_image(info->mlx, info->north.img);
	if (info->south.img != NULL)
		mlx_destroy_image(info->mlx, info->south.img);
	if (info->east.img != NULL)
		mlx_destroy_image(info->mlx, info->east.img);
	if (info->west.img != NULL)
		mlx_destroy_image(info->mlx, info->west.img);
	ft_free_split(info->map);
	if (info->mlx != NULL)
	{
		mlx_destroy_display(info->mlx);
		free(info->mlx);
		info->mlx = NULL;
	}
}
