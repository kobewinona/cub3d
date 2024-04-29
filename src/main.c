/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/29 20:38:28 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	sb_argv_parsing(int argc, char **argv)
{
	if (argc != 2)
	{
		par_error_msg("Only take 2 arguments !!!");
		return (-1);
	}
	return (par_open_cub3d(argv[1]));
}

int	main(int argc, char **argv)
{
	int			fd;
	t_parser	info;

	fd = -1;
	if (parser_init(&info) == -1)
		return (EXIT_FAILURE);
	fd = sb_argv_parsing(argc, argv);
	if (fd == -1)
	{
		parser_free(&info, &fd, NULL);
		return (EXIT_FAILURE);
	}
	parser_job(fd, &info);
	parser_debug(&info, true);
	info.window = mlx_new_window(info.mlx, 1000, 1000, "Cud3D");
	if (info.window == NULL)
	{
		parser_free(&info, &fd, NULL);
		return (EXIT_FAILURE);
	}
	// Your Part
	
	// Your Part
	parser_free(&info, &fd, NULL);
	return (EXIT_SUCCESS);
}
