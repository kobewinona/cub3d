/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 21:56:28 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	par_open_cub3d(const char *path)
{
	int		fd;
	char	*dot_ptr;
	size_t	path_len;

	path_len = ft_strlen(path);
	dot_ptr = ft_strnstr(path, ".cub", path_len);
	if (dot_ptr == NULL)
	{
		par_error_msg("File extension name don't exist");
		return (-1);
	}
	if (ft_strlen(dot_ptr) > sizeof(".cub") - 1)
	{
		par_error_msg("File extension name should be .cub");
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		par_error_msg("Can't open this file");
	return (fd);
}
