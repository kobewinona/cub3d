/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 04:33:06 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 04:36:44 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	par_ismap(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != WALL && line[i] != EMPTY && line[i] != ' ' && \
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