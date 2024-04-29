/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:45:38 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/29 20:59:04 by dklimkin         ###   ########.fr       */
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

static void	update_rays(t_fxy p_pos, t_ray ray, t_fxy *rays, int i)
{
	if (ray.side_dist.x < ray.side_dist.y)
	{
		if (ray.dir.x < 0)
			rays[i].x = ceil(rays[i].x + ray.step.x);
		else
			rays[i].x = floor(rays[i].x + ray.step.x);
		rays[i].y = p_pos.y + (rays[i].x - p_pos.x) * (ray.dir.y / ray.dir.x);
	}
	else
	{
		if (ray.dir.y < 0)
			rays[i].y = ceil(rays[i].y + ray.step.y);
		else
			rays[i].y = floor(rays[i].y + ray.step.y);
		rays[i].x = p_pos.x + (rays[i].y - p_pos.y) * (ray.dir.x / ray.dir.y);
	}
}

static void	preform_dda(t_state *state, t_ray *ray, int i, t_fxy *rays)
{
	ray->step.x = (ray->dir.x > 0) - (ray->dir.x < 0);
	ray->step.y = (ray->dir.y > 0) - (ray->dir.y < 0);
	while (ray->is_obstacle_hit == false)
	{
		ray->is_back_side = ray->side_dist.x < ray->side_dist.y;
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->perp_dist = ray->side_dist.x;
			ray->map.x += ray->step.x;
			update_rays(state->p_pos, (*ray), rays, i);
			ray->side_dist.x += ray->delta_dist.x;
		}
		else
		{
			ray->perp_dist = ray->side_dist.y;
			ray->map.y += ray->step.y;
			update_rays(state->p_pos, (*ray), rays, i);
			ray->side_dist.y += ray->delta_dist.y;
		}
		ray->map.x = clamp(ray->map.x, 0, MAP_WIDTH);
		ray->map.y = clamp(ray->map.y, 0, MAP_HEIGHT);
		ray->is_obstacle_hit = g_test_map[ray->map.y][ray->map.x] > 0;
	}
}

static void	init_ray(t_state *state, t_ray *ray, int x, float angle_increment)
{
	float	current_angle;

	current_angle = (state->p_dir_angle - (FIELD_OF_VIEW / 2))
		+ (x * angle_increment);
	ray->angle = current_angle - state->p_dir_angle;
	ray->dir = (t_fxy){cos(current_angle), sin(current_angle)};
	ray->delta_dist.x = 1 / fabs(ray->dir.x);
	ray->delta_dist.y = 1 / fabs(ray->dir.y);
	if (ray->dir.x == 0)
		ray->delta_dist.x = MY_FLT_MAX;
	if (ray->dir.y == 0)
		ray->delta_dist.y = MY_FLT_MAX;
	ray->map.x = state->p_pos.x;
	ray->map.y = state->p_pos.y;
}

void	handle_raycasting(t_state **state)
{
	t_ray		ray;
	t_fxy		*rays_end_pos;
	float		angle_increment;
	int			x;

	rays_end_pos = (t_fxy *)malloc(SCREEN_WIDTH * sizeof(t_fxy));
	if (!rays_end_pos)
		return ;
	x = 0;
	angle_increment = FIELD_OF_VIEW / (SCREEN_WIDTH - 1);
	while (x < SCREEN_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		init_ray((*state), &ray, x, angle_increment);
		rays_end_pos[x] = (*state)->p_pos;
		calc_step_and_initial_side_dist((*state), &ray);
		preform_dda((*state), &ray, x, rays_end_pos);
		draw_column((*state), ray, x);
		x++;
	}
	(*state)->rays = rays_end_pos;
}
