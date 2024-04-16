/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 23:47:59 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/15 20:59:17 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static bool	sb_is_emptyline(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\n' || line[i] != '\0')
	{
		if (line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
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

// static int	sb_read_element(t_parser *info, char *line, char *elements_find)
// {
// 	size_t	len;
// 	char	**tmp;
// 	int		status;

// 	tmp = ft_split(line, ' ');
// 	if (tmp == NULL)
// 		return (-1);
// 	len = ft_split_len(tmp);
// 	status = sb_element_table(info, tmp, len);
// 	ft_free_split(tmp);
// 	return (status);
// }

// // TODO: think about malloc error

// /*
// RETURN VALUE
// - NORMAL RETURN
// 	0:	success
// 	-1:	allocation failed

// - CAN'T FIND SOME ELEMENT
// 	1:	can't find north
// 	2:	can't find south
// 	4:	can't find west
// 	8:	can't find east
// 	16:	can't find floor
// 	32:	can't find ceil

// - ELEMENT INFO ERROR
// 	2^8:	north file error
// 	2^9:	south file error
// 	2^10:	west file error
// 	2^11:	east file error
// 	2^12:	floor info is wrong
// 	2^13:	ceil info is wrong

// - ELEMENT FIELD INPUT (too much or lack)
// 	2^16:	north input field must be 2
// 	2^17:	south input field must be 2
// 	2^18:	west input field must be 2
// 	2^19:	east input field must be 2
// 	2^20:	floor input field must be 2
// 	2^21:	ceil input field must be 2

// - FINDING MAP TOO EARLY OR NOT FIND AT ALL
// 	2^24:	find map? too early (stop reading map)
// 	2^25:	map doesn't exist in this file (reach eof)
// */

// int	par_get_element(t_parser *info, int fd, char **ext_buff)
// {
// 	char	elements_find;
// 	char	*line;
// 	int		isok;

// 	line = get_next_line_ext_buff(fd, ext_buff);
// 	elements_find = 0;
// 	while (line != NULL && elements_find == 63)
// 	{
// 		if (!sb_is_emptyline(line))
// 			isok = sb_read_element(info, line, &elements_find);
// 		free(line);
// 		if (isok != 0)
// 		{
// 			free(ext_buff);
// 			ext_buff = NULL;
// 			return (-1);
// 		}
// 		line = get_next_line_ext_buff(fd, ext_buff);
// 	}
// 	return (sb_check_element_init(info));
// }

static int	sb_check_element_init(t_parser *info)
{
	if (info->north.img == NULL)
		return (1 << 0);
	if (info->south.img == NULL)
		return (1 << 1);
	if (info->west.img == NULL)
		return (1 << 2);
	if (info->east.img == NULL)
		return (1 << 3);
	if (!info->floor.isinit)
		return (1 << 4);
	if (!info->ceil.isinit)
		return (1 << 5);
	return (0);
}

static int	sb_read_element(t_parser *info, char *line, int *elem_count)
{
	size_t	len;
	char	**box;
	int		status;

	if (sb_is_emptyline(line))
		return (0);
	box = ft_split(line, ' ');
	if (box == NULL)
		return (-1);
	(*elem_count)--;
	len = ft_split_len(box);
	status = sb_elem_table(info, box, len);
	ft_free_split(box);
	return (status);
}

int	par_get_element(t_parser *info, int fd, char **ext_buff)
{
	char	*line;
	int		elem_count;
	int		status;

	status = 0;
	elem_count = 6;
	line = get_next_line_ext_buff(fd, ext_buff);
	while (line != NULL && elem_count > 0 && status != -1)
	{
		status &= sb_read_element(info, line, &elem_count);
		free(line);
		if (status == -1)
			free(ext_buff);
		if (elem_count > 0)
			line = get_next_line_ext_buff(fd, ext_buff);
	}
	return (status & sb_check_element_init(info));
}