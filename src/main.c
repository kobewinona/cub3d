/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/30 12:19:59 by dklimkin         ###   ########.fr       */
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
	int			fd;
	t_parser	info;
	t_state		*state;
	t_win		*win;

	fd = -1;
	if (parser_init(&info) == -1)
		return (EXIT_FAILURE);
	fd = sb_argv_parsing(argc, argv);
	if (fd == -1)
	{
		parser_free(&info, &fd, NULL);
		return (EXIT_FAILURE);
	}
	parser_job(fd, &info);
	parser_debug(&info, true);
	info.window = mlx_new_window(info.mlx, 1000, 1000, "Cud3D");
	if (info.window == NULL)
	{
		parser_free(&info, &fd, NULL);
		return (EXIT_FAILURE);
	}

	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
		return (EXIT_FAILURE);
	ft_memset(state, 0, sizeof(t_state));
	state->log_fd = open("logs.txt", O_WRONLY | O_CREAT | O_TRUNC, 444);
	state->p_pos = (t_fxy){13.629072, 2.428815};
	state->p_dir = (t_fxy){0, -1};
	state->p_dir_angle = atan2(state->p_dir.y, state->p_dir.x);
	state->mov_offset_step = 1;
	state->mov_speed = PLAYER_SPEED;
	state->cam_speed = 0;
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
	return (parser_free(&info, &fd, NULL), game_exit(&state, EXIT_SUCCESS));
}
