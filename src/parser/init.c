/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:11:59 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/15 14:25:58 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_parser	parser_init(void *mlx)
{
	t_parser	info;
	info.mlx = mlx;
	info.north.img = NULL;
	info.south.img = NULL;
	info.west.img = NULL;
	info.east.img = NULL;
	info.floor.isinit = false;
	info.ceil.isinit = false;
	info.map = NULL;
	info.height = 0;
	info.width = 0;
	info.player.face = undefine;
	return (info);
}