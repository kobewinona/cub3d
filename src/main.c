/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/17 00:33:57 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static int	sb_argv_parsing(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		par_error_msg("Only take 2 arguments !!!");
// 		return (-1);
// 	}
// 	return (par_open_cub3d(argv[1]));
// }

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_queue	queue1;
	char	*str1 = "jkdbfnojwae";
	char	*str2 = "nweoufijwef";
	char	*str3 = "ierjflnasdfn";
	char	*str4 = "sbuduvknweu";
	char	*str5 = "nldnlwndndlkm";

	(void)str1;
	(void)str2;
	(void)str3;
	(void)str4;
	(void)str5;
	queue1 = queue_init();	
	t_node	*node1 = node_new(str1);
	t_node	*node2 = node_new(str2);
	t_node	*node3 = node_new(str3);
	t_node	*node4 = node_new(str4);
	t_node	*node5 = node_new(str5);
	queue_queue(&queue1, node1);
	printf("-----------------\n");
	queue_transverse(&queue1);
	printf("-----------------\n");
	
	queue_queue(&queue1, node2);
	queue_queue(&queue1, node3);
	queue_queue(&queue1, node4);
	printf("-----------------\n");
	queue_transverse(&queue1);
	printf("-----------------\n");
	
	t_node *tmp = queue_dequeue(&queue1);
	printf("%s\n", node_extract(tmp));
	tmp = queue_dequeue(&queue1);
	printf("%s\n", node_extract(tmp));
	tmp = queue_dequeue(&queue1);
	printf("%s\n", node_extract(tmp));
	queue_queue(&queue1, node5);
	printf("-----------------\n");
	queue_transverse(&queue1);
	printf("-----------------\n");

	tmp = queue_dequeue(&queue1);
	printf("%s\n", node_extract(tmp));
	tmp = queue_dequeue(&queue1);
	printf("%s\n", node_extract(tmp));
	tmp = queue_dequeue(&queue1);
	printf("%s\n", node_extract(tmp));
	tmp = queue_dequeue(&queue1);
	printf("%s\n", node_extract(tmp));
	printf("-----------------\n");
	queue_transverse(&queue1);
	printf("-----------------\n");

	// running game
	return (EXIT_SUCCESS);
}
