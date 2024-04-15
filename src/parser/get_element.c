/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 23:47:59 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/15 14:08:30 by tponutha         ###   ########.fr       */
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

static bool	sb_element_table(t_parser *info, char **tmp)
{
	(void)info;
	if (ft_strncmp(tmp[0], NORTH_ELEM, sizeof(NORTH_ELEM)))
		return (0);
	if (ft_strncmp(tmp[0], SOUTH_ELEM, sizeof(SOUTH_ELEM)))
		return (0);
	if (ft_strncmp(tmp[0], WEST_ELEM, sizeof(WEST_ELEM)))
		return (0);
	if (ft_strncmp(tmp[0], EAST_ELEM, sizeof(EAST_ELEM)))
		return (0);
	if (ft_strncmp(tmp[0], FLOOR_ELEM, sizeof(FLOOR_ELEM)))
		return (0);
	if (ft_strncmp(tmp[0], CEILING_ELEM, sizeof(CEILING_ELEM)))
		return (0);
	return (false);
}

static bool	sb_read_element(t_parser *info, char *line)
{
	size_t	len;
	char	**tmp;
	bool	status;

	tmp = ft_split(line, ' ');
	if (tmp == NULL)
		return (false);
	len = ft_split_len(tmp);
	if (len != 2)
	{
		par_error_msg("This line should be empty or contain 2 elements");
		ft_free_split(tmp);
		return (false);
	}
	status = sb_element_table(info, tmp);
	ft_free_split(tmp);
	return (status);
}

static int	sb_check_element_init(t_parser *info)
{
	if (info->north.img == NULL)
		return (-1);
	if (info->south.img == NULL)
		return (-1);
	if (info->west.img == NULL)
		return (-1);
	if (info->east.img == NULL)
		return (-1);
	if (!info->floor.isinit)
		return (-1);
	if (!info->ceil.isinit)
		return (-1);
	return (0);
}

// TODO: think about malloc error

int	par_get_element(t_parser *info, int fd, char **ext_buff)
{
	char	*line;
	bool	isok;

	line = get_next_line_ext_buff(fd, ext_buff);
	while (line != NULL)
	{
		if (!sb_is_emptyline(line))
			isok = sb_read_element(info, line);
		free(line);
		if (!isok)
		{
			free(ext_buff);
			ext_buff = NULL;
			return (-1);
		}
		line = get_next_line_ext_buff(fd, ext_buff);
	}
	return (sb_check_element_init(info));
}