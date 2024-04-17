/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/17 17:37:51 by tponutha         ###   ########.fr       */
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
	int		fd;
	t_queue	elemnet;
	char	*ext_buff;
	char	*first_map;

	elemnet = queue_init();
	ext_buff = NULL;
	fd = sb_argv_parsing(argc, argv);
	if (fd == -1)
		return (EXIT_FAILURE);
	// char	*line;
	// char	buff[4];
	// read(fd, buff, 3);
	// buff[3] = 0;
	// printf("%s\n", buff);
	// line = get_next_line(fd);
	// while (line != NULL)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// }
	first_map = par_read_element(&elemnet, fd, &ext_buff);
	free(first_map);
	queue_transverse(&elemnet);
	queue_flush(&elemnet);
	close(fd);
	return (EXIT_SUCCESS);
}
