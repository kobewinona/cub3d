/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:24:45 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 00:12:01 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_queue.h"

t_queue	queue_init(void)
{
	t_queue	queue;

	queue.head = NULL;
	queue.tail = NULL;
	return (queue);
}
