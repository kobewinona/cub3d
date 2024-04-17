/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:24:19 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 23:14:59 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static bool	sb_isnumber(char *color_str)
{
	size_t	i;

	i = 0;
	while (color_str[i] != '\0')
	{
		if (!ft_isdigit(color_str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	sb_str_to_rgb(char **color_value, int rgb[])
{
	if (!sb_isnumber(color_value[0]))
		return (false);
	if (!sb_isnumber(color_value[1]))
		return (false);
	if (!sb_isnumber(color_value[2]))
		return (false);
	rgb[0] = ft_atoi(color_value[0]);
	rgb[1] = ft_atoi(color_value[1]);
	rgb[2] = ft_atoi(color_value[2]);
	if (rgb[0] > 255)
		return (false);
	if (rgb[1] > 255)
		return (false);
	if (rgb[2] > 255)
		return (false);
	return (true);
}

static int	sb_assign(t_parser *info, char **color_value, t_elem_type type)
{
	t_rgb	*ptr_color;
	int		rgb[3];

	if (type == floor_elem)
		ptr_color = &info->floor;
	else if (type == ceil_elem)
		ptr_color = &info->ceil;
	else
		return (-1);
	if (!sb_str_to_rgb(color_value, rgb))
		return (par_element_bitmask(type, data_error));
	ptr_color->r = rgb[0];
	ptr_color->g = rgb[1];
	ptr_color->b = rgb[2];
	ptr_color->isinit = true;
	return (0);
}

int	par_get_color(t_parser *info, char **box, t_elem_type type)
{
	char	**color_value;
	
	if (ft_split_len(box) != 2)
		return (par_element_bitmask(type, args_error));
	color_value = ft_split(color_value, ',');
	if (color_value == NULL)
		return (-1);
	if (ft_split_len(color_value) != 3)
	{
		ft_free_split(color_value);
		return (par_element_bitmask(type, args_error));
	}
	ft_free_split(color_value);
	return (sb_assign(info, color_value, type));
}
