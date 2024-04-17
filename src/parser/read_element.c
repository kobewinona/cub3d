/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 05:23:56 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 17:38:19 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static bool	sb_set_element_bits(int bit, int *element_bits)
{
	if (((*element_bits) & bit) != 0)
		return (false);
	(*element_bits) |= bit;
	return (true);
}

static bool	sb_is_contain_elemnet(char *line, int *element_bits)
{
	size_t	len;

	len = ft_strlen(line);
	if (ft_strnstr(line, "NO ", len) != NULL)
		return (sb_set_element_bits((1 << 0), element_bits));
	if (ft_strnstr(line, "SO ", len) != NULL)
		return (sb_set_element_bits((1 << 1), element_bits));
	if (ft_strnstr(line, "WE ", len) != NULL)
		return (sb_set_element_bits((1 << 2), element_bits));
	if (ft_strnstr(line, "EA ", len) != NULL)
		return (sb_set_element_bits((1 << 3), element_bits));
	if (ft_strnstr(line, "F ", len) != NULL)
		return (sb_set_element_bits((1 << 4), element_bits));
	if (ft_strnstr(line, "C ", len) != NULL)
		return (sb_set_element_bits((1 << 5), element_bits));
	return (false);
}

/*
RETURN VALUE
0: not find
1: find
-1: error
*/

static int	sb_check_element(char *line, t_queue *element, int *element_bits)
{
	t_node	*node;

	if (!sb_is_contain_elemnet(line, element_bits))
		return (0);
	node = node_new(line);
	if (node == NULL)
	{
		free(line);
		return (-1);
	}
	queue_queue(element, node);
	return (1);
}

char	*par_read_element(t_queue *element, int fd, char **ext_buff)
{
	char	*line;
	int		element_bit;

	element_bit = 0;
	line = get_next_line_ext_buff(fd, ext_buff);
	while (line != NULL)
	{
		if (par_ismap(line))
			break ;
		if (!par_isspace(line))
		{
			if (sb_check_element(line, element, &element_bit) == -1)
			{
				free(ext_buff);
				return (NULL);
			}
		}
		else
			free(line);
		line = get_next_line_ext_buff(fd, ext_buff);
	}
	return (line);
}