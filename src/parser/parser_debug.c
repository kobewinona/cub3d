/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/28 17:48:24 by tponutha         ###   ########.fr       */
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

static void	sb_print_map(t_parser *info)
{
	size_t	y;
	size_t	x;

	y = 0;
	printf("----------MAP---------\n");
	printf("Map Dimension : %lux%lu\n\n", info->width, info->height);
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			if (info->map[y][x] == EMPTY)
				printf("\033[0;33m \033[0m");
			else if (info->map[y][x] == WALL)
				printf("\033[0;35m1\033[0m");
			else if (info->map[y][x] == FLOOR)
				printf("0");
			else if (info->map[y][x] == PLAYER)
			{
				if (info->player.face == north)
					printf("N");
				else if (info->player.face == south)
					printf("S");
				else if (info->player.face == west)
					printf("W");
				else if (info->player.face == east)
					printf("\033[0;32mE\033[0m");
				else
					printf("\033[0;32m*\033[0m");
			}
			else
				printf("\033[0;31m%c\033[0m", info->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	parser_debug(t_parser *info, bool isprint)
{
	if (!isprint)
		return ;
	sb_print_elem(info);
	sb_print_player(info);
	sb_print_map(info);
}
