/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:45:38 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/26 22:36:11 by dklimkin         ###   ########.fr       */
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
		ray->is_obstacle_hit = g_test_map[map_y][map_x] > 0;
	}
}

static void	draw(t_state *state, t_ray ray, t_column column, int x)
{
	int	y;

	y = 0;
	while (y < column.wall_start)
	{
		put_pixel_img((*state->canvas), (t_xy){x, y},
			create_color(255, 0, 0, 0));
		y++;
	}
	while (y < column.wall_end)
	{
		put_pixel_img((*state->canvas), (t_xy){x, y},
			create_color(255, 5, 70, 120));
		column.shadow.color = create_color(column.shadow.opacity, 0, 0, 0);
		put_pixel_img((*state->canvas), (t_xy){x, y}, column.shadow.color);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_img((*state->canvas), (t_xy){x, y},
			create_color(255, 0, 0, 0));
		y++;
	}
}

static void	draw_column(t_state *state, t_ray ray, int x)
{
	t_column	column;
	t_shadow	shadow;
	float		exponent;

	column.height = (int)(SCREEN_WIDTH / (ray.perp_dist * cos(ray.angle)));
	column.wall_start = -column.height / 2 + SCREEN_HEIGHT / 2;
	if (column.wall_start < 0)
		column.wall_start = 0;
	column.wall_end = column.height / 2 + SCREEN_HEIGHT / 2;
	if (column.wall_end >= SCREEN_HEIGHT)
		column.wall_end = SCREEN_HEIGHT - 1;
	shadow.max_opacity = 200;
	shadow.factor = 10;
	if (ray.is_back_side)
		shadow.factor = 5;
	exponent = (1 - exp(-(ray.perp_dist / shadow.factor)));
	shadow.opacity = (shadow.max_opacity * exponent);
	if (shadow.opacity > shadow.max_opacity)
		shadow.opacity = shadow.max_opacity;
	column.shadow = shadow;
	draw(state, ray, column, x);
}

void	handle_raycasting(t_state **state)
{
	t_ray		ray;
	float		angle;
	float		angle_i;
	int			x;

	x = 0;
	angle_i = FIELD_OF_VIEW / (SCREEN_WIDTH - 1);
	while (x < SCREEN_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		angle = (((*state)->p_dir_angle - (FIELD_OF_VIEW / 2)) + (x * angle_i));
		ray.angle = angle - (*state)->p_dir_angle;
		ray.dir = (t_xy){cos(angle), sin(angle)};
		ray.end_pos = (*state)->p_pos;
		ray.delta_dist.x = 1 / fabs(ray.dir.x);
		ray.delta_dist.y = 1 / fabs(ray.dir.y);
		if (ray.dir.x == 0)
			ray.delta_dist.x = FLT_MAX;
		if (ray.dir.y == 0)
			ray.delta_dist.y = FLT_MAX;
		calc_step_and_initial_side_dist((*state), &ray);
		preform_dda(&ray, (int)(*state)->p_pos.x, (int)(*state)->p_pos.y);
		draw_column((*state), ray, x);
		x++;
	}
}
