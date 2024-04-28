/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/28 17:33:01 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_texture	*sb_get_ptr(t_parser *info, t_ltype type)
{
	t_texture	*ptr;

	ptr = NULL;
	if (type == north_elem)
		ptr = &info->north;
	else if (type == south_elem)
		ptr = &info->south;
	else if (type == west_elem)
		ptr = &info->west;
	else if (type == east_elem)
		ptr = &info->east;
	return (ptr);
}

static void	sb_add_null_at_newline(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}

int	par_get_texture(char **box, t_parser *info, t_ltype type, bool iserr)
{
	int			height;
	int			width;
	t_texture	*ptr;
	
	ptr = sb_get_ptr(info, type);
	sb_add_null_at_newline(box[1]);
	ptr->img = mlx_xpm_file_to_image(info->mlx, box[1], &width, &height);
	if (ptr->img == NULL)
		return (1);
	if (iserr)
	{
		mlx_destroy_image(info->mlx, ptr->img);
		ptr->img = NULL;
		return (1);
	}
	ptr->width = width;
	ptr->height = height;
	return (0);
}