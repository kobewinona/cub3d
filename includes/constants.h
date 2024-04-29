/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:06:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/29 19:09:24 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define TITLE "cub3d"

// @def dev
# define MY_FLT_MAX 3.402823466e+38F
# define PI 3.14159265358979323846
# define SUCCESS 0
# define FAILURE -1

// @def window
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define PLAYER_SIZE 8
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define FIELD_OF_VIEW 0.8

// @def minimap
# define MINIMAP_PLAYER_SIZE 4
# define MINIMAP_CELL_SIZE 10
# define MINIMAP_WIDTH 180
# define MINIMAP_HEIGHT 180
# define MINIMAP_X -20
# define MINIMAP_Y 20
# define MINIMAP_OPACITY 100

// 800 - 180 - 20 = 600

// @def gameplay
# define VISION_DISTANCE MAP_WIDTH
# define PLAYER_SPEED 0.08
# define CAMERA_SPEED 0.05

// @def keyboard keys values
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

// @def ANSI color values
# define RED "\033[31m"
# define GREY "\033[90m"
# define DARK_GREEN "\033[32m"
# define DARK_BLUE "\033[34m"
# define DARK_PURPLE "\033[35m"
# define DEFAULT "\033[0m"

#endif