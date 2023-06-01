/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_celi_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:57:49 by imurugar          #+#    #+#             */
/*   Updated: 2023/06/01 20:06:31 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vars_fc(t_draw_vars *vars, t_game *game)
{
	vars->ray_dir_x = game->player.dir_x + game->player.plane_x;
	vars->ray_dir_y = game->player.dir_y + game->player.plane_y;
	vars->ray_dir_x1 = game->player.dir_x - game->player.plane_x;
	vars->ray_dir_y1 = game->player.dir_y - game->player.plane_y;
}

void	process_x_screen(int *x, int y, t_draw_vars *vars, t_game *game)
{
	int	color;

	while (*x < W_WIDTH)
	{
		vars->tx = (int)(texWidth * (vars->floor_x \
				- (int)(vars->floor_x))) & (texWidth - 1);
		vars->ty = (int)(texHeight * (vars->floor_y \
				- (int)(vars->floor_y))) & (texHeight - 1);
		vars->floor_x += vars->floor_step_x;
		vars->floor_y += vars->floor_step_y;
		color = game->texture[5][texWidth * vars->ty + vars->tx];
		color = (color >> 1) & 8355711;
		game->zbuffer[y][*x] = color;
		color = game->texture[4][texWidth * vars->ty + vars->tx];
		color = (color >> 1) & 8355711;
		game->zbuffer[W_HEIGH - y - 1][*x] = color;
		(*x)++;
	}
}

void	draw_floor_ceiling(t_game *game)
{
	t_draw_vars	vars;
	int			x;
	int			y;

	init_vars_fc(&vars, game);
	y = 0;
	while (y < W_HEIGH)
	{
		vars.pos = y - W_HEIGH / 2;
		vars.row_distance = (0.5 * W_HEIGH) / vars.pos;
		vars.floor_step_x = vars.row_distance
			* (vars.ray_dir_x1 - vars.ray_dir_x) / W_WIDTH;
		vars.floor_step_y = vars.row_distance
			* (vars.ray_dir_y1 - vars.ray_dir_y) / W_WIDTH;
		vars.floor_x = game->player.pos_x + vars.row_distance * vars.ray_dir_x;
		vars.floor_y = game->player.pos_y + vars.row_distance * vars.ray_dir_y;
		x = 0;
		process_x_screen(&x, y, &vars, game);
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
