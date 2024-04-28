/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/28 17:47:52 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	parser_free(t_parser *info)
{
	if (info->window != NULL)
		mlx_destroy_window(info->mlx, info->window);
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