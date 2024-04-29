/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:45:38 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/29 16:01:46 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_step_and_initial_side_dist(t_state *state, t_ray *ray)
{
	if (ray->dir.x < 0)
		ray->side_dist.x = (state->p_pos.x
				- floor(state->p_pos.x)) * ray->delta_dist.x;
	else
		ray->side_dist.x = (ceil(state->p_pos.x)
				- state->p_pos.x) * ray->delta_dist.x;
	if (ray->dir.y < 0)
		ray->side_dist.y = (state->p_pos.y
				- floor(state->p_pos.y)) * ray->delta_dist.y;
	else
		ray->side_dist.y = (ceil(state->p_pos.y)
				- state->p_pos.y) * ray->delta_dist.y;
}

static void	preform_dda(t_ray *ray, int map_x, int map_y)
{
	int	step_x;
	int	step_y;

	step_x = (ray->dir.x > 0) - (ray->dir.x < 0);
	step_y = (ray->dir.y > 0) - (ray->dir.y < 0);
	while (ray->is_obstacle_hit == false)
	{
		ray->is_back_side = ray->side_dist.x < ray->side_dist.y;
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->perp_dist = ray->side_dist.x;
			map_x += step_x;
			ray->side_dist.x += ray->delta_dist.x;
		}
		else
		{
			ray->perp_dist = ray->side_dist.y;
			map_y += step_y;
			ray->side_dist.y += ray->delta_dist.y;
		}
		map_x = clamp(map_x, 0, MAP_WIDTH);
		map_y = clamp(map_y, 0, MAP_HEIGHT);
		ray->is_obstacle_hit = g_test_map[map_y][map_x] > 0;
	}
}

static int	init_ray(float p_angle, t_ray *ray, int x, float angle_increment)
{
	float	current_angle;

	current_angle = (p_angle - (FIELD_OF_VIEW / 2)) + (x * angle_increment);
	ray->angle = current_angle - p_angle;
	ray->dir = (t_fxy){cos(current_angle), sin(current_angle)};
	ray->end_pos = (t_fxy *)malloc(SCREEN_WIDTH * sizeof(t_fxy));
	if (!ray->end_pos)
		return (FAILURE);
	ray->delta_dist.x = 1 / fabs(ray->dir.x);
	ray->delta_dist.y = 1 / fabs(ray->dir.y);
	if (ray->dir.x == 0)
		ray->delta_dist.x = MY_FLT_MAX;
	if (ray->dir.y == 0)
		ray->delta_dist.y = MY_FLT_MAX;
	return (SUCCESS);
}

void	handle_raycasting(t_state **state)
{
	t_ray		ray;
	float		angle_increment;
	int			x;

	x = 0;
	angle_increment = FIELD_OF_VIEW / (SCREEN_WIDTH - 1);
	while (x < SCREEN_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		if (init_ray((*state)->p_dir_angle, &ray, x, angle_increment))
			return ;
		calc_step_and_initial_side_dist((*state), &ray);
		preform_dda(&ray, (int)(*state)->p_pos.x, (int)(*state)->p_pos.y);
		draw_column((*state), ray, x);
		x++;
	}
}
