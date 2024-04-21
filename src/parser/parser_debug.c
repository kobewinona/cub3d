/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/22 03:15:06 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	parser_debug(t_parser *info, bool isprint)
{
	if (!isprint)
		return ;
	printf("----------ELEMENT---------\n");
	printf("NO : %p\n", info->north.img);
	printf("SO : %p\n", info->south.img);
	printf("WE : %p\n", info->west.img);
	printf("EA : %p\n", info->east.img);
	printf("F : %d,%d,%d", info->floor.r, info->floor.g, info->floor.b);
	printf("C : %d,%d,%d", info->ceil.r, info->ceil.g, info->ceil.b);
	printf("\n----------PLAYER---------\n");
	// printf("X: ")
}
