/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:28:01 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 00:32:22 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_queue.h"

void	queue_queue(t_queue *queue, t_node *node)
{
	if (queue->head == NULL && queue->tail == NULL)
	{
		queue->head = node;
		queue->tail = node;
		return ;
	}
	queue->tail->next = node;
	node->prev = queue->tail;
	queue->tail = node;
}
