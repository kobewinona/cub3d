/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_bitmask.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:56:21 by tponutha          #+#    #+#             */
/*   Updated: 2024/04/17 22:54:16 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	par_element_bitmask(t_elem_type type, t_error_type err)
{
	if (err == no_error)
		return (0);
	return ((1 << type) << err);
}
