/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 05:23:56 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/18 22:09:25 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static bool	sb_set_element_bits(int bit, int *bits, t_ltype *type, t_ltype t1)
{
	*type = t1;
	if (((*bits) & bit) != 0)
		return (false);
	(*bits) |= bit;
	return (true);
}

static bool	sb_is_contain_elemnet(char *line, int *bits, t_ltype *type)
{
	size_t	len;

	len = ft_strlen(line);
	if (ft_strnstr(line, "NO ", len) != NULL)
		return (sb_set_element_bits((1 << 0), bits, type, north_elem));
	if (ft_strnstr(line, "SO ", len) != NULL)
		return (sb_set_element_bits((1 << 1), bits, type, south_elem));
	if (ft_strnstr(line, "WE ", len) != NULL)
		return (sb_set_element_bits((1 << 2), bits, type, west_elem));
	if (ft_strnstr(line, "EA ", len) != NULL)
		return (sb_set_element_bits((1 << 3), bits, type, east_elem));
	if (ft_strnstr(line, "F ", len) != NULL)
		return (sb_set_element_bits((1 << 4), bits, type, floor_elem));
	if (ft_strnstr(line, "C ", len) != NULL)
		return (sb_set_element_bits((1 << 5), bits, type, ceil_elem));
	*type = unidentify;
	return (false);
}

/*
RETURN VALUE
0: not find
1: find
-1: error
*/

static int	sb_check_element(char *line, size_t n, t_queue *element, int *bits)
{
	t_node	*node;
	t_ltype	type;

	if (!sb_is_contain_elemnet(line, bits, &type))
	{
		free(line);
		return (0);
	}
	node = node_new(line, n, type);
	if (node == NULL)
	{
		queue_flush(element);
		free(line);
		return (-1);
	}
	queue_queue(element, node);
	return (1);
}

/*
RETURN VALUE
non-null	: ptr to map line
null		: allocation failed or no map exist
*/

t_node	*par_read_element(t_queue *element, int fd, char **ext_buff, int *bit)
{
	size_t	no;
	char	*line;

	no = 0;
	line = get_next_line_ext_buff(fd, ext_buff);
	while (line != NULL)
	{
		if (!par_isspace(line))
		{
			if (par_ismap(line))
				return (node_new(line, no, map_elem));
			if (sb_check_element(line, no, element, bit) == -1)
			{
				free(*ext_buff);
				(*ext_buff) = NULL;
				return (NULL);
			}
		}
		else
			free(line);
		line = get_next_line_ext_buff(fd, ext_buff);
		no++;
	}
	return (NULL);
}
