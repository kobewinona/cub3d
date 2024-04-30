/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/29 20:27:41 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_print_player(t_parser *info)
{
	printf("----------PLAYER---------\n");
	printf("Player Coordinate: (%d,%d)\n", info->player.x, info->player.y);
	printf("Player Direction: ");
	if (info->player.face == north)
		printf("(N)\n");
	else if (info->player.face == south)
		printf("(S)\n");
	else if (info->player.face == west)
		printf("(W)\n");
	else if (info->player.face == east)
		printf("(E)\n");
	else
		printf("(*)\n");
}

static void	sb_print_elem(t_parser *info)
{
	printf("----------ELEMENT---------\n");
	printf("NO: %p\n", info->north.img);
	printf("SO: %p\n", info->south.img);
	printf("WE: %p\n", info->west.img);
	printf("EA: %p\n", info->east.img);
	printf("F: %d,%d,%d\n", info->floor.r, info->floor.g, info->floor.b);
	printf("C: %d,%d,%d\n", info->ceil.r, info->ceil.g, info->ceil.b);
}

void	parser_debug(t_parser *info, bool isprint)
{
	if (!isprint)
		return ;
	sb_print_elem(info);
	sb_print_player(info);
	par_print_map(info);
}
