/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 21:29:51 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	sb_filter(char **box, t_parser *info, t_ltype type)
{
	int	status;

	if (type == north_elem || type == south_elem || \
		type == west_elem || type == east_elem)
		status = par_get_texture(box, info, type);
	else
		status = par_get_color(box, info, type);
	return (status);
}

static int	sb_set_type(char **box, int *bits, t_ltype *type)
{
	size_t	len;

	if (ft_split_len(box) != 2)
		return (2);
	len = ft_strlen(box[0]);
	if (ft_strncmp(box[0], "NO", len) == 0)
		return (par_set_element_bits(1 << 0, bits, type, north_elem));
	if (ft_strncmp(box[0], "SO", len) == 0)
		return (par_set_element_bits(1 << 1, bits, type, south_elem));
	if (ft_strncmp(box[0], "WE", len) == 0)
		return (par_set_element_bits(1 << 2, bits, type, west_elem));
	if (ft_strncmp(box[0], "EA", len) == 0)
		return (par_set_element_bits(1 << 3, bits, type, east_elem));
	if (ft_strncmp(box[0], "F", len) == 0)
		return (par_set_element_bits(1 << 4, bits, type, floor_elem));
	if (ft_strncmp(box[0], "C", len) == 0)
		return (par_set_element_bits(1 << 5, bits, type, ceil_elem));
	return (2);
}

static int	sb_extract(t_parser *info, t_node *node, t_queue *err)
{
	int		status;
	char	**box;

	box = ft_split(node->str, ' ');
	if (box == NULL)
		return (-1);
	if (sb_set_type(box, &info->init_checker, &node->type) != 2)
	{
		status = sb_filter(box, info, node->type);
		if (status == 1)
			queue_queue(err, node);
	}
	else
	{
		status = 1;
		node->type = unidentify;
		queue_queue(err, node);
	}
	ft_free_split(box);
	return (status);
}

int	par_get_element(t_parser *info, t_queue *element, t_queue *err)
{
	t_node	*node;
	int		status;

	node = queue_dequeue(element);
	while (node != NULL)
	{
		status = sb_extract(info, node, err);
		if (status == 0)
			node_delete(node);
		else if (status == -1)
		{
			node_delete(node);
			queue_flush(element);
			queue_flush(err);
			return (-1);
		}
		node = queue_dequeue(element);
	}
	return (queue_len(err) != 0);
}
