/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:25:06 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/17 20:29:10 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_restore_map(char **map, size_t width, size_t height)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == FLOOR_CHAR)
				map[y][x] = FLOOR;
			x++;
		}
		y++;
	}
}

static void	sb_player(char **map, size_t px, size_t py, t_direction pt)
{
	if (pt == north)
		map[py][px] = FACE_NORTH_CHAR;
	else if (pt == south)
		map[py][px] = FACE_SOUTH_CHAR;
	else if (pt == west)
		map[py][px] = FACE_WEST_CHAR;
	else if (pt == east)
		map[py][px] = FACE_EAST_CHAR;
}

static void	sb_floodfill(t_parser *info, size_t x, size_t y, bool *isok)
{
	if (*isok == false)
		return ;
	if (x == 0 || x == info->width - 1 || y == 0 || y == info->height - 1)
	{
		*isok = false;
		return ;
	}
	if (info->map[y][x] == WALL || info->map[y][x] == FLOOR_CHAR)
		return ;
	if (info->map[y][x] == FLOOR || par_isplayer(info->map[y][x]))
		info->map[y][x] = FLOOR_CHAR;
	else if (info->map[y][x] == EMPTY)
	{
		*isok = false;
		return ;
	}
	sb_floodfill(info, x - 1, y, isok);
	sb_floodfill(info, x + 1, y, isok);
	sb_floodfill(info, x, y + 1, isok);
	sb_floodfill(info, x, y - 1, isok);
}

bool	par_floodfill(t_parser *info)
{
	bool	isok;

	isok = true;
	sb_floodfill(info, info->player.x, info->player.y, &isok);
	sb_restore_map(info->map, info->width, info->height);
	sb_player(info->map, info->player.x, info->player.y, info->player.face);
	return (isok);
}
