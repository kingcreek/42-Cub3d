/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:58:47 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/29 22:56:01 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



/*
void	process_y_wall_screen(int x, t_w_vars *vars, t_game *game)
{
	int	color;
	int	texY;
	int	y;

	y = vars->drawStart;
	while (*y < vars->drawEnd)
	{
		texY = (int)vars->texPos & (texHeight - 1);
		vars->texPos += vars->step;
		color = game->texture[vars->texNum][texHeight * texY + vars->texX];
		if (vars->side == 1)
				color = (color >> 1) & 8355711;
			game->buf[y][x] = color;
		y++;
	}
}
*/
/*
static int	worldMap[mapWidth][mapHeight] =
									{
										{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
										{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1},
										{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
										{1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1},
										{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1},
										{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1},
										{1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1},
										{1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,0,1,1,0,0,0,0,0,1},
										{1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,1},
										{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1},
										{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,1},
										{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1},
										{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,1},
										{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
									};*/
		
static void	calculate_ray(t_game *game, t_w_vars *vars, int x)
{
	vars->cameraX = 2 * x / (double)W_WIDTH - 1;
	vars->rayDirX = game->player.dirX + game->player.planeX * vars->cameraX;
	vars->rayDirY = game->player.dirY + game->player.planeY * vars->cameraX;
	vars->mapX = (int)game->player.posX;
	vars->mapY = (int)game->player.posY;
	vars->deltaDistX = fabs(1 / vars->rayDirX);
	vars->deltaDistY = fabs(1 / vars->rayDirY);
	vars->hit = 0;
}

static void	check_side(t_game *game, t_w_vars *vars)
{
	if (vars->rayDirX < 0)
	{
		vars->stepX = -1;
		vars->sideDistX = (game->player.posX - vars->mapX) * vars->deltaDistX;
	}
	else
	{
		vars->stepX = 1;
		vars->sideDistX = (vars->mapX + 1.0 - game->player.posX) * vars->deltaDistX;
	}
	if (vars->rayDirY < 0)
	{
		vars->stepY = -1;
		vars->sideDistY = (game->player.posY - vars->mapY) * vars->deltaDistY;
	}
	else
	{
		vars->stepY = 1;
		vars->sideDistY = (vars->mapY + 1.0 - game->player.posY) * vars->deltaDistY;
	}
}

static void	perform_dda(t_game *game, t_w_vars *vars)
{
	while (vars->hit == 0)
	{
		if (vars->sideDistX < vars->sideDistY)
		{
			vars->sideDistX += vars->deltaDistX;
			vars->mapX += vars->stepX;
			vars->side = 0;
		}
		else
		{
			vars->sideDistY += vars->deltaDistY;
			vars->mapY += vars->stepY;
			vars->side = 1;
		}
		//Check if ray has hit a wall
		//printf("%d   %d\n", vars->mapX, vars->mapY);
		//ft_print_2d_char_array(game->map.map);
		printf("%d   %d\n", vars->mapY, vars->mapX);
		if (ft_strchr("NESW0", game->map.map[vars->mapY][vars->mapX]) == NULL) //if (game->map.map[vars->mapX][vars->mapY] != '0') 
			vars->hit = 1;
	}
}

static void	fill_texture(t_game *game, t_w_vars *vars)
{
	if (vars->side == 0)
		vars->perpWallDist = (vars->mapX - game->player.posX + (1 - vars->stepX) / 2) / vars->rayDirX;
	else
		vars->perpWallDist = (vars->mapY - game->player.posY + (1 - vars->stepY) / 2) / vars->rayDirY;
	vars->lineHeight = (int)(W_HEIGH / vars->perpWallDist);
	vars->drawStart = -vars->lineHeight / 2 + W_HEIGH / 2;
	if(vars->drawStart < 0)
		vars->drawStart = 0;
	vars->drawEnd = vars->lineHeight / 2 + W_HEIGH / 2;
	if(vars->drawEnd >= W_HEIGH)
		vars->drawEnd = W_HEIGH - 1;
	if (vars->side == 0)
		vars->wallX = game->player.posY + vars->perpWallDist * vars->rayDirY;
	else
		vars->wallX = game->player.posX + vars->perpWallDist * vars->rayDirX;
	vars->wallX -= floor(vars->wallX);
	vars->texX = (int)(vars->wallX * (double)texWidth);
	if (vars->side == 0 && vars->rayDirX > 0)
		vars->texX = texWidth - vars->texX - 1;
	if (vars->side == 1 && vars->rayDirY < 0)
		vars->texX = texWidth - vars->texX - 1;
	vars->step = 1.0 * texHeight / vars->lineHeight;
	vars->texPos = (vars->drawStart - W_HEIGH / 2 + vars->lineHeight / 2) * vars->step;
}

void draw_wall(t_game *game)
{
	int			x;
	int			y;
	int			color;
	int			texY;
	t_w_vars	vars;

	x = 0;
	while (x < W_WIDTH)
	{
		calculate_ray(game, &vars, x);
		check_side(game, &vars);
		perform_dda(game, &vars);
		fill_texture(game, &vars);
		y = vars.drawStart;
		while(y < vars.drawEnd)
		{
			texY = (int)vars.texPos & (texHeight - 1);
			vars.texPos += vars.step;
			if (vars.side == 0 && vars.rayDirX > 0)
    			vars.texNum = 3; // Oeste
			else if (vars.side == 0 && vars.rayDirX < 0)
    			vars.texNum = 2; // Este
			else if (vars.side == 1 && vars.rayDirY > 0)
    			vars.texNum = 1; // Sur
			else if (vars.side == 1 && vars.rayDirY < 0)
    			vars.texNum = 0; // Norte
			color = game->texture[vars.texNum][texHeight * texY + vars.texX];
			if (vars.side == 1)
				color = (color >> 1) & 8355711;
			game->zbuffer[y][x] = color;
			y++;
		}
		x++;	
	}
}