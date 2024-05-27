/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 09:13:45 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_ch_map(t_node *node, t_queue *new_map, t_queue *err)
{
	if (par_ismap(node->str))
		queue_queue(new_map, node);
	else
	{
		node->err_type = data;
		queue_queue(err, node);
	}
}

static int	sb_illegal(t_parser *info, t_queue *map, t_queue *err)
{
	t_node	*node;

	if (err->head == NULL && (info->player.face != no_player \
		&& info->player.face != too_many_player))
		return (0);
	queue_flush(map);
	node = queue_dequeue(err);
	printf("Error\n");
	while (node != NULL)
	{
		printf("illegal charactor in map: %lu: %s", node->line_no, node->str);
		if (ft_strrchr(node->str, '\n') == NULL)
			printf("\n");
		node_delete(node);
		node = queue_dequeue(err);
	}
	if (info->player.face == no_player)
		printf("No player in a Map\n");
	else if (info->player.face == too_many_player)
		printf("Too many player in a Map\n");
	return (1);
}

static int	sb_map(t_queue *maps, t_parser *info)
{
	t_node	*node;
	t_queue	err;
	t_queue	new_map;
	size_t	i;

	i = 0;
	err = queue_init();
	new_map = queue_init();
	node = queue_dequeue(maps);
	while (node != NULL)
	{
		par_find_player_by_line(node->str, i, &info->player);
		sb_ch_map(node, &new_map, &err);
		node = queue_dequeue(maps);
		i++;
	}
	*maps = new_map;
	return (sb_illegal(info, maps, &err));
}

/*
CLOSE FD OUTSIDE OF FUNCTION IN ALL CASES
*/

int	par_read_map(t_queue *maps, t_parser *info)
{
	int		res;

	res = sb_map(maps, info);
	if (res != 0)
		return (res);
	if (info->player.face == too_many_player)
	{
		queue_flush(maps);
		par_error_msg("Too Many Players");
		return (1);
	}
	else if (info->player.face == no_player)
	{
		queue_flush(maps);
		par_error_msg("No Players");
		return (1);
	}
	return (0);
}
