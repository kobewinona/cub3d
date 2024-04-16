/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_transverse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 00:03:08 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 00:26:12 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_queue.h"

void	queue_transverse(t_queue *queue)
{
	size_t	i;
	t_node	*node;

	i = 0;
	node = queue->head;
	while (node != NULL)
	{
		printf("%lu.) %s\n", i, node->str);
		i++;
		node = node->next;
	}
}