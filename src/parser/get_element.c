/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/07 20:25:49 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_filter_elemnet(t_queue *element, t_queue *err)
{
	t_node	*node;
	t_queue	tmp;

	tmp = queue_init();
	node = queue_dequeue(element);
	while (node != NULL)
	{
		if (node->type != map_elem && node->type != unidentify)
			queue_queue(&tmp, node);
		else
			queue_queue(err, node);
		node = queue_dequeue(element);
	}
	*element = tmp;
}

static int	sb_filter(char **box, t_parser *info, t_ltype type, bool *iserr)
{
	int	status;

	if (type == north_elem || type == south_elem || \
		type == west_elem || type == east_elem)
	{
		status = par_get_texture(box, info, type, *iserr);
		if (status != 0)
			*iserr = true;
	}
	else
		status = par_get_color(box, info, type);
	return (status);
}

static int	sb_extract(t_parser *info, t_node *node, t_queue *err, bool *iserr)
{
	int		status;
	char	**box;

	box = ft_split(node->str, ' ');
	if (box == NULL)
		return (-1);
	if (ft_split_len(box) == 2)
	{
		status = sb_filter(box, info, node->type, iserr);
		if (status == 1)
			queue_queue(err, node);
	}
	else
	{
		status = 1;
		node->err_type = args;
		queue_queue(err, node);
	}
	ft_free_split(box);
	return (status);
}

int	par_get_element(t_parser *info, t_queue *element, t_queue *err)
{
	t_node	*node;
	bool	iserr;
	int		status;

	iserr = false;
	sb_filter_elemnet(element, err);
	node = queue_dequeue(element);
	while (node != NULL)
	{
		status = sb_extract(info, node, err, &iserr);
		if (status == 0)
			node_delete(node);
		else if (status == -1)
		{
			queue_flush(element);
			queue_flush(err);
			return (-1);
		}
		node = queue_dequeue(element);
	}
	return (queue_len(err) != 0);
}
