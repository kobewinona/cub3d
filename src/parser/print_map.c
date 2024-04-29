/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:26:16 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/29 20:27:13 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	par_print_map(t_parser *info)
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