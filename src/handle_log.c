/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:36:37 by dklimkin          #+#    #+#             */
/*   Updated: 2024/04/18 21:18:05 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	log_raycast_calculations(t_state **state, t_raycast_calc rc)
{
	// dprintf((*state)->log_fd, "%s: %.6lf; ", "rc.camera_x", rc.camera_x);
	// dprintf((*state)->log_fd, "%s: %.6lf; ", "rc.ray_dir_x", rc.ray_dir_x);
	// dprintf((*state)->log_fd, "%s: %.6lf; ", "rc.ray_dir_y", rc.ray_dir_y);
	// dprintf((*state)->log_fd, "%s: %.6lf; ", "rc.side_dist_x", rc.side_dist_x);
	// dprintf((*state)->log_fd, "%s: %.6lf; ", "rc.side_dist_y", rc.side_dist_y);
	// dprintf((*state)->log_fd, "%s: %.6lf; ", "rc.delta_dist_x", rc.delta_dist_x);
	// dprintf((*state)->log_fd, "%s: %.6lf; ", "rc.delta_dist_y", rc.delta_dist_y);
	// dprintf((*state)->log_fd, "%s: %.6d; ", "rc.step_x", rc.step_x);
	// dprintf((*state)->log_fd, "%s: %.6d; ", "rc.step_y", rc.step_y);
	// dprintf((*state)->log_fd, "%s: %.6d; ", "rc.map_x", rc.map_x);
	// dprintf((*state)->log_fd, "%s: %.6d; ", "rc.map_y", rc.map_y);
	// dprintf((*state)->log_fd, "%s: %.6s; ", "rc.is_obstacle_hit", rc.is_obstacle_hit ? "true" : "false");
	// dprintf((*state)->log_fd, "%s: %.6s; ", "rc.is_obstacle_side", rc.is_obstacle_side ? "true" : "false");
}
