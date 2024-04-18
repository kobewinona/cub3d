/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/19 01:49:44 by tponutha         ###   ########.fr       */
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
	return (true);
}

static t_rgb	*sb_get_ptr(t_parser *info, t_ltype type)
{
	t_rgb	*ptr;

	if (type == floor_elem)
		ptr = &info->floor;
	else if (type == ceil_elem)
		ptr = &info->ceil;
	return (ptr);
}

static int	sb_str_to_rgb(char **color_str, t_rgb *ptr)
{
	int	rgb[3];

	if (!sb_isnumber(color_str[0]))
		return (1);
	if (!sb_isnumber(color_str[1]))
		return (1);
	if (!sb_isnumber(color_str[2]))
		return (1);
	rgb[0] = ft_atoi(color_str[0]);
	rgb[1] = ft_atoi(color_str[1]);
	rgb[2] = ft_atoi(color_str[2]);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (1);
	ptr->r = rgb[0];
	ptr->g = rgb[1];
	ptr->b = rgb[2];
	ptr->isinit = true;
	return (0);
}

int	par_get_color(char **box, t_parser *info, t_ltype type, t_etype *err)
{
	int		status;
	char	**color_str;
	t_rgb	*ptr;

	color_str = ft_split(box[1], ',');
	if (color_str == NULL)
		return (-1);
	if (ft_split_len(color_str) != 3)
	{
		*err = args;
		ft_free_split(color_str);
		return (1);
	}
	ptr = sb_get_ptr(info, type);
	status = sb_str_to_rgb(color_str, ptr);
	ft_free_split(color_str);
	return (status);
}