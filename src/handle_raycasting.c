/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:45:38 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/24 21:27:27 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	calc_step_and_initial_side_dist(t_state *state, t_raycast_calc *rc)
// {
// 	rc->step_x = (rc->ray_dir_x > 0) - (rc->ray_dir_x < 0);
// 	rc->step_y = (rc->ray_dir_y > 0) - (rc->ray_dir_y < 0);
// 	if (rc->ray_dir_x < 0)
// 		rc->side_dist_x = (state->p_pos.x - rc->map_x) * rc->delta_dist_x;
// 	else
// 		rc->side_dist_x = (rc->map_x + 1.0 - state->p_pos.x) * rc->delta_dist_x;
// 	if (rc->ray_dir_y < 0)
// 		rc->side_dist_y = (state->p_pos.y - rc->map_y) * rc->delta_dist_y;
// 	else
// 		rc->side_dist_y = (rc->map_y + 1.0 - state->p_pos.y) * rc->delta_dist_y;
// }

// static void	preform_dda(t_state *state, t_raycast_calc *rc)
// {
// 	while (rc->is_obstacle_hit == false)
// 	{
// 		rc->is_obstacle_side = (rc->side_dist_x >= rc->side_dist_y);
// 		if (rc->side_dist_x < rc->side_dist_y)
// 		{
// 			rc->side_dist_x += rc->delta_dist_x;
// 			rc->map_x += rc->step_x;
// 		}
// 		else
// 		{
// 			rc->side_dist_y += rc->delta_dist_y;
// 			rc->map_y += rc->step_y;
// 		}
// 		rc->is_obstacle_hit = g_test_map[rc->map_y][rc->map_x] > 0;
// 		// printf("rc->is_obstacle_hit %d\n", rc->is_obstacle_hit);
// 	}
// 	draw_line((t_line){{state->p_pos.x * CELL_SIZE, state->p_pos.y
// 		* CELL_SIZE}, {rc->map_x * CELL_SIZE, rc->map_y * CELL_SIZE},
// 		create_color(255, 255, 0, 255)}, (*state->canvas), 0);
// }

// static void	draw_column(t_state *state, t_raycast_calc *rc, int x)
// {
// 	int		line_height;
// 	int		draw_start;
// 	int		draw_end;
// 	double	perp_wall_dist;

// 	perp_wall_dist = (rc->map_y - state->p_pos.y
// 			+ (1 - rc->step_y) / 2) / rc->ray_dir_y;
// 	if (rc->is_obstacle_side == false)
// 		perp_wall_dist = (rc->map_x - state->p_pos.x
// 				+ (1 - rc->step_x) / 2) / rc->ray_dir_x;
// 	line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
// 	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
// 	if (draw_end >= SCREEN_HEIGHT)
// 		draw_end = (SCREEN_HEIGHT - 1);
// 	draw_line((t_line){(t_xy){x, draw_start}, (t_xy){x, draw_end},
// 		create_color(255, 100, 100, 100)},
// 		(*state->canvas), rc->is_obstacle_side);
// }

// void	handle_raycasting(t_state **state)
// {
// 	t_raycast_calc	rc;
// 	int				x;

// 	x = 0;
// 	ft_memset(&rc, 0, sizeof(t_raycast_calc));
// 	while (x < SCREEN_WIDTH)
// 	{
// 		rc.map_x = (int)(*state)->p_pos.x;
// 		rc.map_y = (int)(*state)->p_pos.y;
// 		rc.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
// 		rc.ray_dir_x = (*state)->p_dir.x + (*state)->plane.x * rc.camera_x;
// 		rc.ray_dir_y = (*state)->p_dir.y + (*state)->plane.y * rc.camera_x;
// 		rc.delta_dist_x = fabs(1 / rc.ray_dir_x);
// 		if (rc.ray_dir_x == 0)
// 			rc.delta_dist_x = (double)LONG_MAX;
// 		rc.delta_dist_y = fabs(1 / rc.ray_dir_y);
// 		if (rc.ray_dir_y == 0)
// 			rc.delta_dist_y = (double)LONG_MAX;
// 		rc.is_obstacle_hit = false;
// 		rc.is_obstacle_side = false;
// 		calc_step_and_initial_side_dist((*state), &rc);
// 		preform_dda((*state), &rc);
// 		// draw_column((*state), &rc, x);
// 		// printf("here\n");
// 		x++;
// 	}
// }

// static void	calc_step_and_initial_side_dist(t_state *state, t_raycast_calc *rc)
// {
// 	// rc->step_x = (rc->ray_dir.x > 0) - (rc->ray_dir.x < 0);
// 	// rc->step_y = (rc->ray_dir.y > 0) - (rc->ray_dir.y < 0);
// 	if (rc->ray_dir.x < 0)
// 		rc->side_dist.x = (state->p_pos.x - rc->map_x) * rc->delta_dist.x;
// 	else
// 		rc->side_dist.x = (rc->map_x + 1.0 - state->p_pos.x) * rc->delta_dist.x;
// 	if (rc->ray_dir.y < 0)
// 		rc->side_dist.y = (state->p_pos.y - rc->map_y) * rc->delta_dist.y;
// 	else
// 		rc->side_dist.y = (rc->map_y + 1.0 - state->p_pos.y) * rc->delta_dist.y;
// }

static int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static bool	is_colliding(t_raycast_calc *rc)
{
	if (rc->ray_dir.x < 0)
		rc->map.x = clamp(ceil(rc->ray_end_pos.x - 1), 0, MAP_WIDTH - 1);
	else
		rc->map.x = clamp(rc->ray_end_pos.x, 0 , MAP_WIDTH - 1);
	rc->map_side.x = fabs(floor(rc->ray_end_pos.x));
	if (g_test_map[(int)floor(rc->ray_end_pos.y)][(int)rc->map.x] > 0)
		rc->is_unit_side_x_hit = rc->ray_end_pos.x == rc->map.x
			|| rc->ray_end_pos.x == rc->map_side.x;
	if (rc->ray_dir.y < 0)
		rc->map.y = clamp(ceil(rc->ray_end_pos.y - 1), 0, MAP_HEIGHT - 1);
	else
		rc->map.y = clamp(rc->ray_end_pos.y, 0, MAP_HEIGHT - 1);
	rc->map_side.y = fabs(floor(rc->ray_end_pos.y));
	if (g_test_map[(int)rc->map.y][(int)floor(rc->ray_end_pos.x)] > 0)
		rc->is_unit_side_y_hit = rc->ray_end_pos.y == rc->map.y
			|| rc->ray_end_pos.y == rc->map_side.y;
	return (rc->is_unit_side_x_hit || rc->is_unit_side_y_hit);
}

static void	preform_dda(t_state *state, t_raycast_calc *rc)
{
	if (rc->ray_dir.x < 0)
		rc->ray_end_pos.x = floor(rc->ray_end_pos.x);
	else
		rc->ray_end_pos.x = ceil(rc->ray_end_pos.x);
	if (rc->ray_dir.y < 0)
		rc->ray_end_pos.y = floor(rc->ray_end_pos.y);
	else
		rc->ray_end_pos.y = ceil(rc->ray_end_pos.y);
	

	// printf("is_colliding %d\n", is_colliding(rc));

	draw_line((t_line){{state->p_pos.x * CELL_SIZE, state->p_pos.y * CELL_SIZE},
	{rc->ray_end_pos.x * CELL_SIZE, rc->ray_end_pos.y * CELL_SIZE},
		create_color(255, 255, 0, 255)}, (*state->canvas), 0);
}

void	handle_raycasting(t_state **state)
{
	t_raycast_calc	rc;
	int				x;

	x = 0;
	ft_memset(&rc, 0, sizeof(t_raycast_calc));
	while (x < SCREEN_WIDTH)
	{
		rc.map = (*state)->p_pos;
		rc.map_x = (int)(*state)->p_pos.x;
		rc.map_y = (int)(*state)->p_pos.y;
		rc.ray_start_pos = (*state)->p_pos;
		rc.ray_end_pos = (*state)->p_pos;
		rc.ray_dir = (*state)->p_dir;
		rc.delta_dist.x = fabs(1 / rc.ray_dir.x);
		if (rc.ray_dir.x == 0)
			rc.delta_dist.x = FLT_MAX;
		rc.delta_dist.y = fabs(1 / rc.ray_dir.y);
		if (rc.ray_dir.y == 0)
			rc.delta_dist.y = FLT_MAX;
		preform_dda((*state), &rc);
		x++;
	}
}
