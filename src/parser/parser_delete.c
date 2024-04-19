/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/20 02:41:15 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	parser_free(t_parser *info)
{
	// size_t	i;

	// i = 0
	if (info->window != NULL)
		mlx_destroy_window(info->mlx, info->window);
	if (info->north.img != NULL)
		mlx_destroy_image(info->mlx, info->north.img);
	if (info->north.img != NULL)
		mlx_destroy_image(info->mlx, info->north.img);
	if (info->north.img != NULL)
		mlx_destroy_image(info->mlx, info->north.img);
	if (info->north.img != NULL)
		mlx_destroy_image(info->mlx, info->north.img);
	free(info->mlx);
	// while (i < info->height)
}


// going to toilet elsewhere