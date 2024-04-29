/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:35:13 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/16 13:04:44 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_map_value(int object)
{
	if (object == 0)
	{
		ft_putstr_fd(GREY, STDOUT_FILENO);
		ft_putstr_fd("▢", STDOUT_FILENO);
	}
	if (object >= 1)
	{
		ft_putstr_fd(DEFAULT, STDOUT_FILENO);
		ft_putstr_fd("▣", STDOUT_FILENO);
	}
}

void	print_map(int map[MAP_HEIGHT][MAP_WIDTH])
{
	int	y;
	int	x;

	if (!map)
		return ;
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			print_map_value(map[y][x]);
			x++;
			if (x < MAP_WIDTH)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		y++;
	}
}
