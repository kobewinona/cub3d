/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 21:30:33 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_err_str(char *line, size_t no, t_ltype type, t_etype etype)
{
	if (etype == args)
		printf("Must contain 2 arguments: %lu: %s", no, line);
	else if (type == unidentify)
		printf("Unidentify element: %lu: %s", no, line);
	else if (type == floor_elem || type == ceil_elem)
		printf("Wrong RGB format [0-255,0-255,0-255]: %lu: %s", no, line);
	else
		printf("xpm file error or permission denied: %lu: %s", no, line);
}

static void	sb_print_uninit(int init_checker)
{
	if ((init_checker & (1 << 0)) == 0)
		printf("NO: not found\n");
	if ((init_checker & (1 << 1)) == 0)
		printf("SO: not found\n");
	if ((init_checker & (1 << 2)) == 0)
		printf("WE: not found\n");
	if ((init_checker & (1 << 3)) == 0)
		printf("EA: not found\n");
	if ((init_checker & (1 << 4)) == 0)
		printf("F: not found\n");
	if ((init_checker & (1 << 5)) == 0)
		printf("C: not found\n");
}

static void	sb_print_elem_error(t_queue *err)
{
	t_node	*node;

	node = queue_dequeue(err);
	while (node != NULL)
	{
		sb_err_str(node->str, node->line_no, node->type, node->err_type);
		node_delete(node);
		node = queue_dequeue(err);
	}
}

static bool	sb_is_elem_init(t_parser *info, t_queue *err)
{
	if (info->north.img == NULL)
		return (false);
	if (info->south.img == NULL)
		return (false);
	if (info->west.img == NULL)
		return (false);
	if (info->east.img == NULL)
		return (false);
	if (!info->floor.isinit)
		return (false);
	if (!info->ceil.isinit)
		return (false);
	return (err->head == NULL);
}

bool	par_elem_error(t_parser *info, t_queue *map, t_queue *elem, t_queue *e)
{
	if (sb_is_elem_init(info, e))
		return (true);
	printf("Error\n");
	printf("Element Error (ignore checking map)\n");
	queue_flush(elem);
	queue_flush(map);
	sb_print_uninit(info->init_checker);
	sb_print_elem_error(e);
	parser_free(info);
	return (false);
}
