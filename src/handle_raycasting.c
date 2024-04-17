/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:45:38 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/17 22:38:11 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_raycasting(t_state **state)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // x-coordinate in camera space
		double rayDirX = (*state)->p_dir.x + (*state)->plane.x * cameraX;
		double rayDirY = (*state)->p_dir.y + (*state)->plane.y * cameraX;

		// Calculate position and direction of the ray
		int mapX = (int)(*state)->p_pos.x;
		int mapY = (int)(*state)->p_pos.y;
		double sideDistX, sideDistY;

		// Length of ray from one side to next in map
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX, stepY;
		int hit = 0; // Was a wall hit?
		int side;	 // Was the wall vertical or horizontal?

		// Calculate step and initial side distance
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = ((*state)->p_pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - (*state)->p_pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = ((*state)->p_pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - (*state)->p_pos.y) * deltaDistY;
		}

		// Perform DDA
		while (hit == 0)
		{
			// Jump to next map square
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if the ray has hit a wall
			if (testMap[mapY][mapX] > 0)
				hit = 1;
		}

		draw_line((t_line){
            {(*state)->p_pos.x * CELL_SIZE, (*state)->p_pos.y * CELL_SIZE},
            {mapX * CELL_SIZE, mapY * CELL_SIZE},
            create_color(255, 255, 0, 255)  // Green for rays
        }, (*(*state)->canvas), 0);

		// Calculate distance to the point of impact
		if (side == 0)
			perpWallDist = (mapX - (*state)->p_pos.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - (*state)->p_pos.y + (1 - stepY) / 2) / rayDirY;

		// Calculate height of the line to draw on the screen
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		// Calculate lowest and highest pixel to fill in the current stripe
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		// Draw the pixels of the stripe as a vertical line (use your drawing functions)
		draw_line((t_line){{x, drawStart}, (t_xy){x, drawEnd}, create_color(255, 100, 100, 100)}, (*(*state)->canvas), side);
	}
}
