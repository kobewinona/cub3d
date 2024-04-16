/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_dequeue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:27:59 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 00:32:46 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_queue.h"

t_node	*queue_dequeue(t_queue *queue)
{
	t_node	*node;

	if (queue->head == NULL)
		return (NULL);
	if (queue->head == queue->tail)
	{
		node = queue->head;
		node->prev = NULL;
		node->next = NULL;
		queue->head = NULL;
		queue->tail = NULL;
		return (node);
	}
	node = queue->tail;
	queue->tail = queue->tail->prev;
	queue->tail->next = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}