/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/26 19:31:32 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_exit(t_state **state, int exit_status)
{
	mlx_destroy_window((*state)->win->mlx_ptr, (*state)->win->win_ptr);
	close((*state)->log_fd);
	if (exit_status != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	exit(exit_status);
}

int	main(void)
{
	t_state	*state;
	t_win	*win;

	print_map(g_test_map);
	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
		return (EXIT_FAILURE);
	ft_memset(state, 0, sizeof(t_state));
	state->log_fd = open("logs.txt", O_WRONLY | O_CREAT | O_TRUNC, 444);
	state->p_pos = (t_xy){13.629072, 2.428815};
	state->p_dir = (t_xy){0, -1};
	state->p_dir_angle = atan2(state->p_dir.y, state->p_dir.x);
	if (create_window(SCREEN_WIDTH, SCREEN_HEIGHT, &win) == FAILURE)
		return (EXIT_FAILURE);
	state->win = win;
	state->canvas = create_image(
			SCREEN_WIDTH, SCREEN_HEIGHT, state->win->mlx_ptr);
	mlx_loop_hook(win->mlx_ptr, render_game, &state);
	mlx_hook(win->win_ptr, 02, (1L << 0), read_keys_pressed, &state);
	mlx_hook(win->win_ptr, 03, (1L << 1), read_keys_released, &state);
	mlx_hook(win->win_ptr, 17, 0, game_exit, &state);
	mlx_loop(win->mlx_ptr);
	return (game_exit(&state, EXIT_SUCCESS));
}
