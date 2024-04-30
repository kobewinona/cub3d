/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:58:38 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 00:23:58 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_queue.h"

char	*node_extract(t_node *node)
{
	char	*line;

	if (node == NULL)
		return (NULL);
	line = node->str;
	free(node);
	return (line);
}
