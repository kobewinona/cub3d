/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:47:50 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 21:35:13 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static bool	sb_is_this_player(char c, t_player *player)
{
	if ((c == FACE_NORTH_CHAR || c == FACE_SOUTH_CHAR || c == FACE_WEST_CHAR \
		|| c == FACE_EAST_CHAR) && player->face != no_player)
	{
		player->face = too_many_player;
		return (false);
	}
	else if (c == FACE_NORTH_CHAR)
		player->face = north;
	else if (c == FACE_SOUTH_CHAR)
		player->face = south;
	else if (c == FACE_WEST_CHAR)
		player->face = west;
	else if (c == FACE_EAST_CHAR)
		player->face = east;
	else
		return (false);
	return (true);
}

void	par_find_player_by_line(char *line, size_t line_no, t_player *player)
{
	size_t	i;

	i = 1;
	while (line[i] != '\0')
	{
		if (player->face == too_many_player)
			return ;
		if (sb_is_this_player(line[i], player))
		{
			player->x = i;
			player->y = line_no;
		}
		i++;
	}
}
