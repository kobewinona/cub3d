/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:51:40 by tponutha          #+#    #+#             */
/*   Updated: 2024/05/15 07:03:40 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	sb_init_player(t_player *player)
{
	player->face = no_player;
	player->x = 0;
	player->y = 0;
}

static void	sb_init_texture(t_texture *texture)
{
	texture->img = NULL;
	texture->width = 0;
	texture->height = 0;
}

static void	sb_init_rgb(t_rgb *rgb)
{
	rgb->r = 0;
	rgb->g = 0;
	rgb->b = 0;
	rgb->isinit = false;
}

static void	sb_init_map(t_parser *info)
{
	info->map = NULL;
	info->width = 0;
	info->height = 0;
}

int	parser_init(t_parser *info)
{
	info->mlx = mlx_init();
	if (info->mlx == NULL)
		return (-1);
	info->init_checker = 0;
	info->window = NULL;
	sb_init_map(info);
	sb_init_player(&info->player);
	sb_init_texture(&info->north);
	sb_init_texture(&info->south);
	sb_init_texture(&info->west);
	sb_init_texture(&info->east);
	sb_init_rgb(&info->floor);
	sb_init_rgb(&info->ceil);
	return (0);
}
