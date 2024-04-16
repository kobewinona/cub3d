/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:06:01 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/16 19:08:35 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define SUCCESS 0
# define FAILURE -1

# define TITLE "cub3d"

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define CELL_SIZE 34
# define SCREEN_WIDTH 816
# define SCREEN_HEIGHT 816

# define PLAYER_SPEED 0.05
# define CAMERA_SPEED 0.05

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define KEY_PRESS 02
# define KEY_RELEASE 03
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)

// colors
# define RED "\033[31m"
# define GREY "\033[90m"
# define DARK_GREEN "\033[32m"
# define DARK_BLUE "\033[34m"
# define DARK_PURPLE "\033[35m"
# define DEFAULT "\033[0m"


#endif