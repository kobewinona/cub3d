/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:32:55 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 09:02:28 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_queue	sb_flush(char *str, t_queue *elem, t_queue *map, t_queue *err)
{
	par_error_msg(str);
	queue_flush(elem);
	queue_flush(map);
	queue_flush(err);
	return (queue_init());
}

static t_queue	sb_element_part(int fd, t_parser *info)
{
	t_queue	elem;
	t_queue	err;
	t_queue	map;

	elem = queue_init();
	err = queue_init();
	map = queue_init();
	if (par_read_cub3d(fd, &map) != 0)
		return (sb_flush("par_read_map(): malloc failed", &elem, &map, &err));
	par_filter(&map, &elem);
	if (map.head == NULL)
		return (sb_flush("No Map", &elem, &map, &err));
	if (par_get_element(info, &elem, &err) == -1)
		return (sb_flush("par_get_elem(): malloc failed", &elem, &map, &err));
	if (!par_elem_error(info, &map, &elem, &err))
		return (queue_init());
	return (map);
}

static bool	sb_map_part(t_queue *map, t_parser *info)
{
	info->map = par_get_map(map, info);
	if (info->map == NULL)
	{
		par_error_msg("Map Allocation failed");
		return (false);
	}
	if (!par_floodfill(info))
	{
		par_error_msg("Floodfill Error");
		par_print_map(info);
		return (false);
	}
	return (true);
}

void	parser_job(int fd, t_parser *info)
{
	t_queue	map;

	map = sb_element_part(fd, info);
	if (map.head == NULL)
	{
		parser_free(info);
		exit(EXIT_FAILURE);
	}
	if (par_read_map(&map, info) != 0)
	{
		parser_free(info);
		exit(EXIT_FAILURE);
	}
	if (!sb_map_part(&map, info))
	{
		parser_free(info);
		exit(EXIT_FAILURE);
	}
}
