/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/24 23:31:46 by tponutha         ###   ########.fr       */
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
	t_queue		element;
	t_queue		maps;
	t_queue		err;
	char		*ext_buff;
	t_node		*first_map;

	element = queue_init();
	err = queue_init();
	maps = queue_init();
	ext_buff = NULL;
	if (parser_init(&info) == -1)
	{
		return (EXIT_FAILURE);
	}
	fd = sb_argv_parsing(argc, argv);
	if (fd == -1)
		return (EXIT_FAILURE);
	first_map = par_read_element(&element, fd, &ext_buff, &info.init_checker);
	if (first_map == NULL)
	{
		par_error_msg("Allocation failed or Map isn't exist");
		close(fd);
		queue_flush(&element);
		queue_flush(&err);
		// TODO: delete parser
		return (EXIT_FAILURE);
	}
	queue_queue(&maps, first_map);
	if (par_get_element(&info, &element, &err) == -1)
	{
		par_error_msg("Allocation failed");
		close(fd);
		queue_flush(&maps);
		// TODO: delete parser
		return (EXIT_FAILURE);
	}
	par_element_error(fd, ext_buff, &info, &err);

	int status = par_read_map(first_map, fd, &ext_buff, &info);
	if (status == -1)
	{
		// TODO: write a function that clear every variable
		par_error_msg("Allocation failed");
		return (EXIT_FAILURE);
	}
	else if (status == 1)
	{
		// TODO: write a function that clear every variable
		// par_error_msg("Allocation failed");
		return (EXIT_FAILURE);
	}
	info.map = par_get_map(&maps, &info);
	if (info.map == NULL)
	{
		// TODO: write a function that clear every variable
		par_error_msg("Allocation failed");
		return (EXIT_FAILURE);
	}
	
	free(ext_buff);
	queue_flush(&err);
	queue_flush(&element);
	close(fd);
	parser_free(&info);
	return (EXIT_SUCCESS);
}
