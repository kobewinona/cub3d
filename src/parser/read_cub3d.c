/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:20:55 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 20:36:34 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	sb_malloc_fail(char *line, char *ext_buff, t_queue *map, int fd)
{
	close(fd);
	free(line);
	free(ext_buff);
	queue_flush(map);
	return (-1);
}

static char	*sb_gnl_wrapper(int fd, char **ext_buff)
{
	size_t	nl_pos;
	char	*line;

	line = get_next_line_ext_buff(fd, ext_buff);
	if (line == NULL)
		return (NULL);
	nl_pos = ft_strclen(line, '\n');
	line[nl_pos] = '\0';
	return (line);
}

int	par_read_cub3d(int fd, t_queue *map)
{
	size_t	no;
	t_node	*node;
	char	*ext_buff;
	char	*line;

	no = 0;
	ext_buff = NULL;
	line = sb_gnl_wrapper(fd, &ext_buff);
	while (line != NULL)
	{
		node = node_new(line, no, unidentify);
		if (node == NULL)
			return (sb_malloc_fail(line, ext_buff, map, fd));
		queue_queue(map, node);
		line = sb_gnl_wrapper(fd, &ext_buff);
		no++;
	}
	close(fd);
	if (line == NULL && errno == ENOMEM)
		return (sb_malloc_fail(NULL, ext_buff, map, fd));
	return (0);
}

void	par_filter(t_queue *map, t_queue *element)
{
	t_node	*run;

	while (map->head != NULL)
	{
		if (par_isspace(map->head->str))
			node_delete(queue_dequeue(map));
		else
		{
			if (par_ismap(map->head->str))
				return ;
			run = queue_dequeue(map);
			queue_queue(element, run);
		}
	}
}
