/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/22 06:16:01 by tponutha         ###   ########.fr       */
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
	else if (par_ismap(node->str))
		queue_queue(maps, node);
	else
	{
		node->err_type = data;
		queue_queue(err, node);
	}
	return (true);
}

static void	sb_find_player(char *line, t_player *player)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (player->face == too_many_player)
			return ;
		if ((line[i] == FACE_NORTH_CHAR || line[i] == FACE_SOUTH_CHAR || \
			line[i] == FACE_WEST_CHAR || line[i] == FACE_EAST_CHAR) && \
			player->face != no_player)
			player->face = too_many_player;
		else if (line[i] == FACE_NORTH_CHAR)
			player->face = north;
		else if (line[i] == FACE_SOUTH_CHAR)
			player->face = south;
		else if (line[i] == FACE_WEST_CHAR)
			player->face = west;
		else if (line[i] == FACE_EAST_CHAR)
			player->face = east;
		i++;
	}
}

static t_queue	sb_illegal(t_queue *map, t_queue *err)
{
	t_node	*node;
	
	if (err->head == NULL)
		return (*map);
	queue_flush(map);
	node = queue_dequeue(err);
	while (node != NULL)
	{
		printf("illegal charactor in map: %lu: %s", node->line_no, node->str);
		if (ft_strrchr(node->str, '\n') == NULL)
			printf("\n");
		node_delete(node);
		node = queue_dequeue(err);
	}
	return (queue_init());
}

static t_queue	sb_map(t_node *node, int fd, char **ext_buff, t_parser *info)
{
	char	*line;
	t_queue	err;
	t_queue	maps;
	size_t	no;
	
	no = node->line_no;
	err = queue_init();
	maps = queue_init();
	queue_queue(&maps, node);
	line = get_next_line_ext_buff(fd, ext_buff);
	while (line != NULL)
	{
		sb_find_player(line, &info->player);
		if (!sb_check_map(&maps, &err, node_new(line, no, map_elem), line))
		{
			free(*ext_buff);
			*ext_buff = NULL;
			return (maps);
		}
		line = get_next_line_ext_buff(fd, ext_buff);
		no++;
	}
	return (sb_illegal(&maps, &err));
}

t_queue par_read_map(t_node *node, int fd, char **ext_buff, t_parser *info)
{
	t_queue	maps;
	size_t	width;
	size_t	height;
	char	**box;
	
	maps = sb_map(node, fd, ext_buff, info);
	if (maps.head == NULL)
		return (maps);
	if (info->player.face == too_many_player)
	{
		queue_flush(&maps);
		printf("Too many players");
	}
	else if (info->player.face == no_player)
	{
		queue_flush(&maps);
		printf("No players");
	}
	return (maps);
}
