/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:43:39 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/18 21:51:22 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_queue.h"

t_node	*node_new(char *line, size_t line_no, t_ltype type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->str = line;
	node->line_no = line_no;
	node->err_type = uncheck;
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
