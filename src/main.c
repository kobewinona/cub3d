/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:03:16 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/27 14:13:11 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_exit(t_state **state, int exit_status)
{
	mlx_destroy_image((*state)->info.mlx, (*state)->canvas->img_ptr);
	free((*state)->canvas);
	mlx_destroy_window((*state)->info.mlx, (*state)->win->win_ptr);
	free((*state)->win);
	if ((*state)->rays)
		free((*state)->rays);
	mlx_destroy_image((*state)->info.mlx, (*state)->info.north.img);
	mlx_destroy_image((*state)->info.mlx, (*state)->info.south.img);
	mlx_destroy_image((*state)->info.mlx, (*state)->info.west.img);
	mlx_destroy_image((*state)->info.mlx, (*state)->info.east.img);
	ft_free_split((*state)->info.map);
	mlx_destroy_display((*state)->info.mlx);
	free((*state)->info.mlx);
	free((*state));
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

static int	init_state(t_state **state, t_parser info)
{
	(*state) = (t_state *)malloc(sizeof(t_state));
	if (!(*state))
		return (FAILURE);
	ft_memset((*state), 0, sizeof(t_state));
	(*state)->p_pos = (t_fxy){(info.player.x + 0.5), (info.player.y + 0.5)};
	if (info.player.face == north)
		(*state)->p_dir = (t_fxy){0, -1};
	else if (info.player.face == south)
		(*state)->p_dir = (t_fxy){0, 1};
	else if (info.player.face == west)
		(*state)->p_dir = (t_fxy){-1, 0};
	else if (info.player.face == east)
		(*state)->p_dir = (t_fxy){1, 0};
	(*state)->p_dir_angle = atan2((*state)->p_dir.y, (*state)->p_dir.x);
	(*state)->mov_offset_step = 1;
	(*state)->mov_speed = PLAYER_SPEED;
	(*state)->cam_speed = 0;
	(*state)->info = info;
	return (SUCCESS);
}

static int	run_mlx(t_state **state)
{
	if (create_window((*state)->info.mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, &((*state)->win)) == FAILURE)
		return (EXIT_FAILURE);
	if (!(*state)->win || !(*state)->info.mlx || !(*state)->win->win_ptr)
		return (game_exit(state, EXIT_FAILURE));
	(*state)->canvas = create_image(
			(*state)->info.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!(*state)->canvas || !(*state)->canvas->img_ptr)
		return (game_exit(state, EXIT_FAILURE));
	mlx_loop_hook((*state)->info.mlx, render_game, state);
	mlx_hook((*state)->win->win_ptr, 02, (1L << 0), read_keys_pressed, state);
	mlx_hook((*state)->win->win_ptr, 03, (1L << 1), read_keys_released, state);
	mlx_hook((*state)->win->win_ptr, 17, 0, game_exit, state);
	mlx_loop((*state)->info.mlx);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_parser	info;
	t_state		*state;

	fd = -1;
	if (parser_init(&info) == -1)
		return (EXIT_FAILURE);
	fd = sb_argv_parsing(argc, argv);
	if (fd == -1)
		return (parser_free(&info, &fd, NULL), EXIT_FAILURE);
	parser_job(fd, &info);
	if (parser_debug(&info, false))
		return (parser_free(&info, &fd, NULL), EXIT_SUCCESS);
	if (init_state(&state, info) == FAILURE)
		return (game_exit(&state, EXIT_FAILURE));
	if (run_mlx(&state) == FAILURE)
		return (game_exit(&state, EXIT_FAILURE));
	return (game_exit(&state, EXIT_SUCCESS));
}
