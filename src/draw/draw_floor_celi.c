/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_celi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:57:44 by imurugar          #+#    #+#             */
/*   Updated: 2023/07/13 21:03:01 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * The function "draw_floor_ceiling" fills the floor and ceiling
 * of the game window with the specified colors.
 * 
 * @param game A pointer to a struct called "t_game" 
 * which contains information about the game state and settings.
 */
void	draw_floor_ceiling(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < W_HEIGH)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			color = game->map.floor_color;
			game->zbuffer[y][x] = color;
			color = game->map.ceil_color;
			game->zbuffer[W_HEIGH - y - 1][x] = color;
			x++;
		}
		y++;
	}
}

/**
 * The function performs the digital differential analyzer
 * (DDA) algorithm to calculate the distance to
 * the next wall in a raycasting process.
 * 
 * @param game The parameter `game` is a pointer to a `t_game`
 * struct. This struct likely contains
 * information about the game state, such as the map and player position.
 * @param vars The `vars` parameter is a pointer to a structure 
 * `t_w_vars` which contains various
 * variables used in the DDA (Digital Differential Analyzer) algorithm.
 * These variables include `hit`,
 * `side_dist_x`, `side_dist_y`, `delta_dist_x`, `delta_dist_y`, `map
 */
void	perform_dda(t_game *game, t_w_vars *vars)
{
	while (vars->hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			vars->side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			vars->side = 1;
		}
		if (ft_strchr("NESW0", game->map.map[vars->map_y][vars->map_x]) == NULL)
			vars->hit = 1;
	}
}
