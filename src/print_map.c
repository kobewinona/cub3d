/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:35:13 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/12 16:04:10 by dklimkin         ###   ########.fr       */
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
	t_xy	pos;

	if (!map)
		return ;
	pos = (t_xy){0, 0};
	while (pos.y < MAP_HEIGHT)
	{
		pos.x = 0;
		while (pos.x < MAP_WIDTH)
		{
			print_map_value(map[pos.y][pos.x]);
			pos.x++;
			if (pos.x < MAP_WIDTH)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		pos.y++;
	}
}
