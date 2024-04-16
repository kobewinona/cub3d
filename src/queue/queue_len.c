/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 03:25:49 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 03:28:17 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_queue.h"

size_t	queue_len(t_queue *queue)
{
	size_t	len;
	t_node	*node;

	len = 0;
	node = queue->head;
	while (node != NULL)
	{
		node = node->next;
		len++;
	}
	return (len);
}
