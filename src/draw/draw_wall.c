/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:58:47 by imurugar          #+#    #+#             */
/*   Updated: 2023/06/01 13:52:08 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_ray(t_game *game, t_w_vars *vars, int x)
{
	vars->camera_x = 2 * x / (double)W_WIDTH - 1;
	vars->ray_dir_x = game->player.dir_x + game->player.plane_x
		* vars->camera_x;
	vars->ray_dir_y = game->player.dir_y + game->player.plane_y
		* vars->camera_x;
	vars->map_x = (int)game->player.pos_x;
	vars->map_y = (int)game->player.pos_y;
	vars->delta_dist_x = fabs(1 / vars->ray_dir_x);
	vars->delta_dist_y = fabs(1 / vars->ray_dir_y);
	vars->hit = 0;
}

static void	check_side(t_game *game, t_w_vars *vars)
{
	if (vars->ray_dir_x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (game->player.pos_x - vars->map_x)
			* vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - game->player.pos_x)
			* vars->delta_dist_x;
	}
	if (vars->ray_dir_y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (game->player.pos_y - vars->map_y)
			* vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - game->player.pos_y)
			* vars->delta_dist_y;
	}
}

static void	fill_texture(t_game *game, t_w_vars *vars)
{
	vars->perp_wall_dist = (vars->map_y - game->player.pos_y
			+ (1 - vars->step_y) / 2) / vars->ray_dir_y;
	if (vars->side == 0)
		vars->perp_wall_dist = (vars->map_x - game->player.pos_x
				+ (1 - vars->step_x) / 2) / vars->ray_dir_x;
	vars->line_height = (int)(W_HEIGH / vars->perp_wall_dist);
	vars->draw_start = -vars->line_height / 2 + W_HEIGH / 2;
	if (vars->draw_start < 0)
		vars->draw_start = 0;
	vars->draw_end = vars->line_height / 2 + W_HEIGH / 2;
	if (vars->draw_end >= W_HEIGH)
		vars->draw_end = W_HEIGH - 1;
	vars->wall_x = game->player.pos_x + vars->perp_wall_dist * vars->ray_dir_x;
	if (vars->side == 0)
		vars->wall_x = game->player.pos_y + vars->perp_wall_dist
			* vars->ray_dir_y;
	vars->wall_x -= floor(vars->wall_x);
	vars->tex_x = (int)(vars->wall_x * (double)texWidth);
	if (vars->side == 0 && vars->ray_dir_x > 0)
		vars->tex_x = texWidth - vars->tex_x - 1;
	if (vars->side == 1 && vars->ray_dir_y < 0)
		vars->tex_x = texWidth - vars->tex_x - 1;
	vars->step = 1.0 * texHeight / vars->line_height;
	vars->tex_pos = (vars->draw_start - W_HEIGH / 2
			+ vars->line_height / 2) * vars->step;
}

static void	fill_buffer(t_game *game, t_w_vars *vars, int x, int y)
{
	int	color;
	int	tex_y;

	tex_y = (int)vars->tex_pos & (texHeight - 1);
	vars->tex_pos += vars->step;
	vars->tex_num = 0;
	if (vars->side == 0 && vars->ray_dir_x > 0)
		vars->tex_num = 3;
	else if (vars->side == 0 && vars->ray_dir_x < 0)
		vars->tex_num = 2;
	else if (vars->side == 1 && vars->ray_dir_y > 0)
		vars->tex_num = 1;
	color = game->texture[vars->tex_num][texHeight * tex_y + vars->tex_x];
	if (vars->side == 1)
		color = (color >> 1) & 8355711;
	game->zbuffer[y][W_WIDTH - x - 1] = color;
}

void	draw_wall(t_game *game)
{
	int			x;
	int			y;
	t_w_vars	vars;

	x = 0;
	while (x < W_WIDTH)
	{
		calculate_ray(game, &vars, x);
		check_side(game, &vars);
		perform_dda(game, &vars);
		fill_texture(game, &vars);
		y = vars.draw_start;
		while (y < vars.draw_end)
		{
			fill_buffer(game, &vars, x, y);
			y++;
		}
		x++;
	}
}
