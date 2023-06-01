/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_celi_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:57:49 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/31 13:29:25 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vars(t_draw_vars *vars, t_game *game)
{
	vars->rayDirX0 = game->player.dirX - game->player.planeX;
	vars->rayDirY0 = game->player.dirY - game->player.planeY;
	vars->rayDirX1 = game->player.dirX + game->player.planeX;
	vars->rayDirY1 = game->player.dirY + game->player.planeY;
}

void	process_x_screen(int *x, int y, t_draw_vars *vars, t_game *game)
{
	int	color;
	int	floor_texture;
	int	ceiling_texture;

	floor_texture = 3;
	ceiling_texture = 6;
	while (*x < W_WIDTH)
	{
		vars->tx = (int)(texWidth * (vars->floorX - (int)(vars->floorX))) \
			& (texWidth - 1);
		vars->ty = (int)(texHeight * (vars->floorY - (int)(vars->floorY))) \
			& (texHeight - 1);
		vars->floorX += vars->floorStepX;
		vars->floorY += vars->floorStepY;
		color = game->texture[floor_texture][texWidth * vars->ty + vars->tx];
		color = (color >> 1) & 8355711;
		game->zbuffer[y][*x] = color;
		color = game->texture[ceiling_texture][texWidth * vars->ty + vars->tx];
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
	int			color;

	init_vars(&vars, game);
	y = 0;
	while (y < W_HEIGH)
	{
		vars.pos = y - W_HEIGH / 2;
		vars.rowDistance = (0.5 * W_HEIGH) / vars.pos;
		vars.floorStepX = vars.rowDistance * (vars.rayDirX1 - vars.rayDirX0) \
			/ W_WIDTH;
		vars.floorStepY = vars.rowDistance * (vars.rayDirY1 - vars.rayDirY0) \
			/ W_WIDTH;
		vars.floorX = game->player.posX + vars.rowDistance * vars.rayDirX0;
		vars.floorY = game->player.posY + vars.rowDistance * vars.rayDirY0;
		x = 0;
		process_x_screen(&x, y, &vars, game);
		y++;
	}
}
