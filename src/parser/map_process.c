/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:18:59 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/24 21:56:40 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static size_t	sb_find_max_width(t_queue *map)
{
	size_t	len;
	size_t	max;
	t_node	*node;

	node = map->head;
	max = 0;
	while (node != NULL)
	{
		len = ft_strclen(node->str, '\n');
		if (len > max)
			max = len;
		node = node->next;
	}
	return (max);
}

static char	sb_assign_value(char c)
{
	if (c == WALL_CHAR)
		return (WALL);
	else if (c == FLOOR_CHAR)
		return (FLOOR);
	else if (c == ' ')
		return (EMPTY);
	return (c);
}

static char	*sb_get_newline(char *old_line, size_t width)
{
	char	*new_line;
	size_t	old_len;
	size_t	i;

	new_line = malloc(sizeof(char) * width);
	if (new_line == NULL)
		return (NULL);
	old_len = ft_strclen(old_line, '\n');
	i = 0;
	while (i <= width)
	{
		if (i >= old_len)
			new_line[i] = EMPTY;
		else
			new_line[i] = sb_assign_value(old_line[i]);
		i++;
	}
	return (new_line);
}

static char	**sb_map_transform(char **map, t_queue *map_queue, t_parser *info)
{
	char	*new_line;
	t_node	*node;
	size_t	i;

	i = 0;
	node = queue_dequeue(map_queue);
	while (node != NULL)
	{
		new_line = sb_get_newline(node->str, info->width);
		node_delete(node);
		if (new_line == NULL)
		{
			queue_flush(map_queue);
			ft_free_split(map);
			return (NULL);
		}
		map[i] = new_line;
		i++;
		node = queue_dequeue(map_queue);
	}
	return (map);
}

char	**par_get_map(t_queue *map_queue, t_parser *info)
{
	char	**map;

	info->width = sb_find_max_width(map_queue);
	info->height = queue_len(map_queue);
	map = ft_calloc(sizeof(char *), info->height + 1);
	if (map == NULL)
	{
		par_error_msg("Map Allocation failed");
		return (NULL);
	}
	if (sb_map_transform(map, map_queue, info) == NULL)
	{
		par_error_msg("Map Allocation failed");
		return (NULL);
	}
	info->map = map;
	return (map);
}
