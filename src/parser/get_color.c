/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/27 21:36:00 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static bool	sb_isnumber(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (str[0] != '\0');
}

static t_rgb	*sb_get_ptr(t_parser *info, t_ltype type)
{
	t_rgb	*ptr;

	ptr = NULL;
	if (type == floor_elem)
		ptr = &info->floor;
	else if (type == ceil_elem)
		ptr = &info->ceil;
	return (ptr);
}

static int	sb_str_to_rgb(char **color_str, t_rgb *ptr)
{
	if (!sb_isnumber(color_str[0]))
		return (1);
	if (!sb_isnumber(color_str[1]))
		return (1);
	if (!sb_isnumber(color_str[2]))
		return (1);
	ptr->r = ft_atoi(color_str[0]);
	ptr->g = ft_atoi(color_str[1]);
	ptr->b = ft_atoi(color_str[2]);
	if (ptr->r > 255 || ptr->g > 255 || ptr->b > 255)
		return (1);
	ptr->isinit = true;
	return (0);
}

int	par_get_color(char **box, t_parser *info, t_ltype type)
{
	int		status;
	char	**color_str;
	t_rgb	*ptr;

	color_str = ft_split(box[1], ',');
	if (color_str == NULL)
		return (-1);
	if (ft_split_len(color_str) != 3)
	{
		ft_free_split(color_str);
		return (1);
	}
	ptr = sb_get_ptr(info, type);
	status = sb_str_to_rgb(color_str, ptr);
	ft_free_split(color_str);
	return (status);
}
