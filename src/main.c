/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/17 20:49:09 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_exit(t_win *win, int exit_status)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (exit_status != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	exit(exit_status);
}

int	main(void)
{
	t_state	*state;
	t_win	*win;

	print_map(testMap);
	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
		return (EXIT_FAILURE);
	ft_memset(state, 0, sizeof(t_state));
	state->p_pos = (t_xy){22, 19};
	state->p_dir = (t_xy){-1, 0};
	state->plane = (t_xy){0, 0.66};
	if (create_window(SCREEN_WIDTH, SCREEN_HEIGHT, &win) == FAILURE)
		return (EXIT_FAILURE);
	state->win = win;
	state->canvas = create_image(
			SCREEN_WIDTH, SCREEN_HEIGHT, state->win->mlx_ptr);
	mlx_loop_hook(win->mlx_ptr, render_game, &state);
	mlx_hook(win->win_ptr, 02, (1L << 0), read_keys, &state);
	mlx_hook(win->win_ptr, 03, (1L << 1), release_keys, &state);
	mlx_hook(win->win_ptr, 17, 0, game_exit, win);
	mlx_loop(win->mlx_ptr);
	return (game_exit(win, EXIT_SUCCESS));
}
