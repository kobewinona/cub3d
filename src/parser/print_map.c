/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:26:16 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 22:19:00 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_print_player(char c)
{
	if (c == north)
		printf("\033[0;32mN\033[0m");
	else if (c == south)
		printf("\033[0;32mS\033[0m");
	else if (c == west)
		printf("\033[0;32mW\033[0m");
	else if (c == east)
		printf("\033[0;32mE\033[0m");
	else
		printf("\033[0;33m*\033[0m");
}

static void	sb_print_banner(size_t width, size_t height)
{
	printf("----------MAP---------\n");
	printf("Map Dimension : %lux%lu\n\n", width, height);
}

void	par_print_map(t_parser *info)
{
	size_t	y;
	size_t	x;

	y = 0;
	sb_print_banner(info->width, info->height);
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
				sb_print_player(info->map[y][x]);
			else
				printf("\033[0;31m%c\033[0m", info->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
