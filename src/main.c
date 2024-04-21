/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/22 03:07:00 by tponutha         ###   ########.fr       */
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
	t_queue		err;
	char		*ext_buff;
	char		*first_map;

	element = queue_init();
	err = queue_init();
	ext_buff = NULL;
	if (parser_init(&info) == -1)
	{
		return (EXIT_FAILURE);
	}
	fd = sb_argv_parsing(argc, argv);
	if (fd == -1)
		return (EXIT_FAILURE);
	first_map = par_read_element(&element, fd, &ext_buff, &info.init_checker);
	free(first_map);
	
	printf("Ready for extracting\n");
	int status = par_get_element(&info, &element, &err);
	printf("Finish extracting\n");
	
	(void)status;
	par_element_error(fd, ext_buff, &info, &err);
	
	free(ext_buff);
	queue_flush(&err);
	queue_flush(&element);
	close(fd);
	parser_free(&info);
	return (EXIT_SUCCESS);
}
