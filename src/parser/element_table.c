/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:16:33 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/15 21:20:27 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	par_elem_table(t_parser *info, char **box, size_t len, char *elem_check)
{
	(void)info;
	if (ft_strncmp(box[0], NORTH_ELEM, sizeof(NORTH_ELEM)))
	{
		if ((*elem_check & (1 << 0)) != 0)
			return (1 << 26);
	}
		return (0);
	if (ft_strncmp(box[0], SOUTH_ELEM, sizeof(SOUTH_ELEM)))
		return (0);
	if (ft_strncmp(box[0], WEST_ELEM, sizeof(WEST_ELEM)))
		return (0);
	if (ft_strncmp(box[0], EAST_ELEM, sizeof(EAST_ELEM)))
		return (0);
	if (ft_strncmp(box[0], FLOOR_ELEM, sizeof(FLOOR_ELEM)))
		return (0);
	if (ft_strncmp(box[0], CEILING_ELEM, sizeof(CEILING_ELEM)))
		return (0);
	return (1 << 24);
}

static int	sb_elem_table(t_parser *info, char **box, size_t len)
{
	(void)info;
	if (ft_strncmp(box[0], NORTH_ELEM, sizeof(NORTH_ELEM)))
		return (0);
	if (ft_strncmp(box[0], SOUTH_ELEM, sizeof(SOUTH_ELEM)))
		return (0);
	if (ft_strncmp(box[0], WEST_ELEM, sizeof(WEST_ELEM)))
		return (0);
	if (ft_strncmp(box[0], EAST_ELEM, sizeof(EAST_ELEM)))
		return (0);
	if (ft_strncmp(box[0], FLOOR_ELEM, sizeof(FLOOR_ELEM)))
		return (0);
	if (ft_strncmp(box[0], CEILING_ELEM, sizeof(CEILING_ELEM)))
		return (0);
	return (1 << 24);
}