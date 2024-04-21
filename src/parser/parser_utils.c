/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 07:51:07 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/22 05:03:52 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	par_ismap(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			break ;
		if (line[i] != WALLS && line[i] != EMPTY && line[i] != ' ' && \
			line[i] != FACE_NORTH && line[i] != FACE_SOUTH && \
			line[i] != FACE_EAST && line[i] != FACE_WEST)
				return (false);
		i++;
	}
	return (true);
}

bool	par_isspace(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

bool	par_set_element_bits(int bit, int *bits, t_ltype *type, t_ltype t1)
{
	*type = t1;
	if (((*bits) & bit) != 0)
		return (false);
	(*bits) |= bit;
	return (true);
}
