/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:28:04 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/18 17:06:54 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_queue.h"

void	queue_flush(t_queue *queue)
{
	t_node	*tmp;

	while (queue->head != NULL)
	{
		tmp = queue_dequeue(queue);
		node_delete(tmp);
	}
}
