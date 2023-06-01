/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_celi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:57:44 by imurugar          #+#    #+#             */
/*   Updated: 2023/06/01 13:48:05 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
