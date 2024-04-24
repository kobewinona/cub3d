/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/24 23:07:27 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static bool	sb_check_map(t_queue *maps, t_queue *err, t_node *node, char *line)
{
	if (node == NULL)
	{
		free(line);
		queue_flush(maps);
		queue_flush(err);
		return (false);
	}
	if (par_ismap(node->str))
		queue_queue(maps, node);
	else
	{
		node->err_type = data;
		queue_queue(err, node);
	}
	return (true);
}

static int	sb_illegal(t_queue *map, t_queue *err)
{
	t_node	*node;
	
	if (err->head == NULL)
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
	return (1);
}

static int	sb_map(t_queue *maps, int fd, char **ext_buff, t_parser *info)
{
	char	*line;
	t_queue	err;
	size_t	no;
	
	no = maps->head->line_no;
	err = queue_init();
	line = get_next_line_ext_buff(fd, ext_buff);
	while (line != NULL)
	{
		par_find_player_by_line(line, no, &info->player);
		if (!sb_check_map(&maps, &err, node_new(line, no, map_elem), line))
		{
			free(*ext_buff);
			*ext_buff = NULL;
			return (-1);
		}
		line = get_next_line_ext_buff(fd, ext_buff);
		no++;
	}
	if (errno == ENOMEM)
		return (-1);
	return (sb_illegal(&maps, &err));
}

/*
CLOSE FD OUTSIDE OF FUNCTION IN ALL CASES
*/

int par_read_map(t_queue *maps, int fd, char **ext_buff, t_parser *info)
{
	size_t	width;
	size_t	height;
	char	**box;
	
	if (sb_map(maps, fd, ext_buff, info))
		return (-1);
	if (info->player.face == too_many_player)
	{
		queue_flush(&maps);
		par_error_msg("Too Many Players");
		return (1);
	}
	else if (info->player.face == no_player)
	{
		queue_flush(&maps);
		par_error_msg("No Players");
		return (1);
	}
	return (0);
}
