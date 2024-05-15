/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:11:34 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/15 07:00:00 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QUEUE_H
# define FT_QUEUE_H
# include <stdlib.h>

typedef enum e_err_type
{
	uncheck,
	no,
	data,
	args
}	t_etype;

typedef enum e_line_type
{
	unidentify,
	north_elem,
	south_elem,
	west_elem,
	east_elem,
	floor_elem,
	ceil_elem,
	map_elem
}	t_ltype;

typedef struct s_node
{
	char			*str;
	size_t			line_no;
	t_etype			err_type;
	t_ltype			type;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_queue
{
	t_node	*head;
	t_node	*tail;
}	t_queue;

t_queue	queue_init(void);
void	queue_flush(t_queue *queue);
void	queue_queue(t_queue *queue, t_node *node);
t_node	*queue_dequeue(t_queue *queue);
void	queue_transverse(t_queue *queue);
size_t	queue_len(t_queue *queue);

t_node	*node_new(char *line, size_t line_no, t_ltype type);
char	*node_extract(t_node *node);
void	node_delete(t_node *node);

#endif