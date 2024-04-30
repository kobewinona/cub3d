/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:35:54 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/29 20:39:59 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free_split(char **arr)
{
	size_t	index;

	if (arr == NULL)
		return ;
	index = 0;
	while (arr[index])
	{
		free(arr[index]);
		index++;
	}
	free(arr);
}