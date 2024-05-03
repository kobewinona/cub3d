/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_put_scanline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:59:55 by dklimkin          #+#    #+#             */
/*   Updated: 2024/05/03 22:22:23 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_wall(t_state *state, t_scanline *scanline)
{
	t_rgb	tex_pixel;
	float	wall_offset;

	wall_offset = (scanline->wall_start
			- (SCREEN_HEIGHT / 2 - scanline->height / 2));
	scanline->tex_findex = wall_offset
		* (1.0 * scanline->tex.height / scanline->height);
	while (scanline->y < scanline->wall_end)
	{
		scanline->tex_index.y = (int)scanline->tex_findex
			% scanline->tex.height;
		scanline->tex_findex += scanline->step_y;
		tex_pixel = get_color_from_img(scanline->tex.img,
				clamp(scanline->tex_index.x, 0, scanline->tex.width),
				clamp(scanline->tex_index.y, 0, scanline->tex.height));
		put_pxl((*state->canvas), (t_fxy){scanline->x, scanline->y},
			create_color(255, tex_pixel.r, tex_pixel.g, tex_pixel.b));
		scanline->shadow.color = create_color(
				scanline->shadow.opacity, 0, 0, 0);
		put_pxl((*state->canvas), (t_fxy){scanline->x, scanline->y},
			scanline->shadow.color);
		scanline->y++;
	}
}

static void	put(t_state *state, t_ray ray, t_scanline *scanline)
{
	while (scanline->y < scanline->wall_start)
	{
		put_pxl((*state->canvas), (t_fxy){scanline->x, scanline->y},
			create_color(255, state->info.ceil.r,
				state->info.ceil.g, state->info.ceil.b));
		scanline->y++;
	}
	put_wall(state, scanline);
	while (scanline->y < SCREEN_HEIGHT)
	{
		put_pxl((*state->canvas), (t_fxy){scanline->x, scanline->y},
			create_color(255, state->info.floor.r,
				state->info.floor.g, state->info.floor.b));
		scanline->y++;
	}
}

static void	set_texture_data(t_state *state, t_ray ray, t_scanline *scanline)
{
	if (ray.is_back_side)
	{
		if (ray.dir.x > 0)
			scanline->tex = state->info.west;
		else
			scanline->tex = state->info.east;
		scanline->tex_index.x = (fmod(state->rays[scanline->x].y, 1.0)
				* scanline->tex.width);
	}
	else
	{
		if (ray.dir.y > 0)
			scanline->tex = state->info.south;
		else
			scanline->tex = state->info.north;
		scanline->tex_index.x = (fmod(state->rays[scanline->x].x, 1.0)
				* scanline->tex.width);
	}
	scanline->tex.width -= 1;
	scanline->tex.height -= 1;
	scanline->step_y = ((1.0 * scanline->tex.height) / scanline->height);
}

static void	set_scanline_data(t_state *state, t_ray ray, t_scanline *scanline)
{
	t_shadow	shadow;
	float		exponent;
	int			wall_start;
	int			wall_end;

	scanline->height = (int)(SCREEN_WIDTH / (ray.perp_dist * cos(ray.angle)));
	scanline->wall_start = -scanline->height / 2 + SCREEN_HEIGHT / 2;
	if (scanline->wall_start < 0)
		scanline->wall_start = 0;
	scanline->wall_end = scanline->height / 2 + SCREEN_HEIGHT / 2;
	if (scanline->wall_end >= SCREEN_HEIGHT)
		scanline->wall_end = SCREEN_HEIGHT - 1;
	shadow.max_opacity = 200;
	shadow.factor = 10;
	if (ray.is_back_side)
		shadow.factor = 5;
	exponent = (1 - exp(-(ray.perp_dist / shadow.factor)));
	shadow.opacity = (shadow.max_opacity * exponent);
	if (shadow.opacity > shadow.max_opacity)
		shadow.opacity = shadow.max_opacity;
	scanline->shadow = shadow;
	set_texture_data(state, ray, scanline);
}

void	put_scanline(t_state *state, t_ray ray, int x)
{
	t_scanline	scanline;

	scanline.x = x;
	scanline.y = 0;
	set_scanline_data(state, ray, &scanline);
	put(state, ray, &scanline);
}
