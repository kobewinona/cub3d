/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:42:34 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/18 00:24:34 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

// static bool	sb_init_checker(int status)
// {
// 	if 
// }

static int	sb_init_element(char *line, t_parser *info, int status)
{
	char	**box;

	box = ft_split(line, ' ');
	if (box == NULL)
		return (-1);
	if (ft_strncmp(box[0], NORTH_ELEM, sizeof(NORTH_ELEM)) == 0)
		status |= par_get_texture(info, box, north_elem);
	else if (ft_strncmp(box[0], SOUTH_ELEM, sizeof(SOUTH_ELEM)) == 0)
		status |= par_get_texture(info, box, south_elem);
	else if (ft_strncmp(box[0], WEST_ELEM, sizeof(WEST_ELEM)) == 0)
		status |= par_get_texture(info, box, west_elem);
	else if (ft_strncmp(box[0], EAST_ELEM, sizeof(EAST_ELEM)) == 0)
		status |= par_get_texture(info, box, east_elem);
	else if (ft_strncmp(box[0], FLOOR_ELEM, sizeof(FLOOR_ELEM)) == 0)
		status |= par_get_color(info, box, floor_elem);
	else if (ft_strncmp(box[0], CEILING_ELEM, sizeof(CEILING_ELEM)) == 0)
		status |= par_get_color(info, box, ceil_elem);
	else
		status |= (1 << 24);
	ft_free_split(box);
	return (status);
}

int	par_get_element(t_parser *info, t_queue *element)
{
	t_node	*node;
	char	*line;
	int		status;

	status = 0;
	node = queue_dequeue(element);
	while (node != NULL)
	{
		line = node_extract(node);
		
		free(line);
		node = queue_dequeue(element);
	}
}
