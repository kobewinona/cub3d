/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/14 18:45:20 by tponutha         ###   ########.fr       */
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
	void		*mlx;
	// t_parser	info;

	fd = sb_argv_parsing(argc, argv);
	if (fd == -1)
		return (EXIT_FAILURE);
	mlx = mlx_init();
	if (mlx == NULL)
	{
		par_error_msg("mlx initialize failed");
		close(fd);
		return (EXIT_FAILURE);
	}
	// parsing function;

	close(fd);

	// running game
	return (EXIT_SUCCESS);
}
