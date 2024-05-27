/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 09:43:24 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	sb_wildcard(t_parser *info)
{
	info->mlx = NULL;
	info->north.img = NULL;
	info->south.img = NULL;
	info->west.img = NULL;
	info->east.img = NULL;
	info->map = NULL;
}

void	parser_free(t_parser *info)
{
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
	}
	sb_wildcard(info);
}
