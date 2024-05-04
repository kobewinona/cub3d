/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:32:55 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/01 20:31:35 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_queue	sb_element_part(int fd, char **ext_buff, t_parser *info)
{
	t_node	*first_map;
	t_queue	element;
	t_queue	err;
	t_queue	map;

	element = queue_init();
	err = queue_init();
	map = queue_init();
	first_map = par_read_element(&element, fd, ext_buff, &info->init_checker);
	if (first_map == NULL)
		return (map);
	queue_queue(&map, first_map);
	if (par_get_element(info, &element, &err) == -1)
	{
		queue_flush(&map);
		return (map);
	}
	if (!par_element_error(fd, *ext_buff, info, &err))
		queue_flush(&map);
	return (map);
}

static bool	sb_map_part(t_queue *map, t_parser *info)
{
	info->map = par_get_map(map, info);
	if (info->map == NULL)
	{
		par_error_msg("Allocation failed");
		return (false);
	}
	if (!par_floodfill(info))
	{
		par_error_msg("Floodfill Error");
		par_print_map(info);
		return (true);
	}
	return (true);
}

void	parser_job(int fd, t_parser *info)
{
	char	*ext_buff;
	t_queue	map;
	int		status;

	ext_buff = NULL;
	map = sb_element_part(fd, &ext_buff, info);
	if (map.head == NULL)
		exit(EXIT_FAILURE);
	status = par_read_map(&map, fd, &ext_buff, info);
	if (status == -1)
		par_error_msg("Allocation failed");
	if (status != 0)
	{
		parser_free(info, &fd, &ext_buff);
		exit(EXIT_FAILURE);
	}
	if (!sb_map_part(&map, info))
	{
		parser_free(info, &fd, &ext_buff);
		exit(EXIT_FAILURE);
	}
	close(fd);
}
