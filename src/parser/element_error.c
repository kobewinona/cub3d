/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/22 03:00:55 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_err_str(char *line, size_t no, t_ltype type, t_etype etype)
{
	char	*ptr;

	ptr = ft_strrchr(line, '\n');
	if (etype == args)
		printf("Must contain 2 arguments: %lu: %s", no, line);
	else if (type == unidentify)
		printf("Unidentify element: %lu: %s", no, line);
	else if (type == floor_elem || type == ceil_elem)
		printf("Wrong RGB format [0-255,0-255,0-255]: %lu: %s", no, line);
	else
		printf("xpm file error or permission denied: %lu: %s", no, line);
	if (ptr == NULL)
		printf("\n");
}

static void	sb_print_uninit(int init_checker)
{
	if ((init_checker & (1 << 0)) == 0)
		printf("NO: not found\n");
	if ((init_checker & (1 << 1)) == 0)
		printf("SO: not found\n");
	if ((init_checker & (1 << 2)) == 0)
		printf("WE: not found\n");
	if ((init_checker & (1 << 3)) == 0)
		printf("EA: not found\n");
	if ((init_checker & (1 << 4)) == 0)
		printf("F: not found\n");
	if ((init_checker & (1 << 5)) == 0)
		printf("C: not found\n");
}

static void	sb_print_elem_error(t_queue *err)
{
	t_node	*node;

	node = queue_dequeue(err);
	while (node != NULL)
	{
		sb_err_str(node->str, node->line_no, node->type, node->err_type);
		node_delete(node);
		node = queue_dequeue(err);
	}
}

void	par_element_error(int fd, char *ext_buff, t_parser *info, t_queue *err)
{
	if (err->head == NULL)
		return ;
	printf("Error\n");
	printf("Element Error (ignore checking map)\n");
	sb_print_uninit(info->init_checker);
	sb_print_elem_error(err);
	parser_free(info);
	close(fd);
	free(ext_buff);
	exit(EXIT_FAILURE);
}