/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:14:36 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/30 16:25:05 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_ad_position(t_game *game, t_player *player)
{
	char	**map;

	map = game->map.map;
	if (game->keys.key_d)
	{
		if (ft_strchr("NESW0", map[(int)(player->posY + \
			player->dirX * MOVE_SPEED)][(int)(player->posX)]) != NULL)
			player->posY += player->dirX * MOVE_SPEED;
		if (ft_strchr("NESW0", map[(int)(player->posY)][(int)(player->posX - \
			player->dirY * MOVE_SPEED)]) != NULL)
			player->posX -= player->dirY * MOVE_SPEED;
	}
	if (game->keys.key_a)
	{
		if (ft_strchr("NESW0", map[(int)(player->posY - \
			player->dirX * MOVE_SPEED)][(int)(player->posX)]) != NULL)
			player->posY -= player->dirX * MOVE_SPEED;
		if (ft_strchr("NESW0", map[(int)(player->posY)][(int)(player->posX + \
			player->dirY * MOVE_SPEED)]) != NULL)
			player->posX += player->dirY * MOVE_SPEED;
	}
}

void	process_ws_position(t_game *game, t_player *player)
{
	char	**map;

	map = game->map.map;
	if (game->keys.key_w)
	{
		if (ft_strchr("NESW0", map[(int)(player->posY + \
			player->dirY * MOVE_SPEED)][(int)(player->posX)]) != NULL)
			player->posY += player->dirY * MOVE_SPEED;
		if (ft_strchr("NESW0", map[(int)(player->posY)][(int)(player->posX + \
			player->dirX * MOVE_SPEED)]) != NULL)
			player->posX += player->dirX * MOVE_SPEED;
	}
	if (game->keys.key_s)
	{
		if (ft_strchr("NESW0", map[(int)(player->posY - \
			player->dirY * MOVE_SPEED)][(int)(player->posX)]) != NULL)
			player->posY -= player->dirY * MOVE_SPEED;
		if (ft_strchr("NESW0", map[(int)(player->posY)][(int)(player->posX - \
			player->dirX * MOVE_SPEED)]) != NULL)
			player->posX -= player->dirX * MOVE_SPEED;
	}
}

void	process_angle(t_game *game, t_player *p)
{
	double	old_dirx;
	double	old_planex;

	if (game->keys.key_right)
	{
		old_dirx = p->dirX;
		p->dirX = p->dirX * cos(ROT_SPEED) - p->dirY * sin(ROT_SPEED);
		p->dirY = old_dirx * sin(ROT_SPEED) + p->dirY * cos(ROT_SPEED);
		old_planex = p->planeX;
		p->planeX = p->planeX * cos(ROT_SPEED) - p->planeY * sin(ROT_SPEED);
		p->planeY = old_planex * sin(ROT_SPEED) + p->planeY * cos(ROT_SPEED);
	}
	else if (game->keys.key_left)
	{
		old_dirx = p->dirX;
		p->dirX = p->dirX * cos(-ROT_SPEED) - p->dirY * sin(-ROT_SPEED);
		p->dirY = old_dirx * sin(-ROT_SPEED) + p->dirY * cos(-ROT_SPEED);
		old_planex = p->planeX;
		p->planeX = p->planeX * cos(-ROT_SPEED) - p->planeY * sin(-ROT_SPEED);
		p->planeY = old_planex * sin(-ROT_SPEED) + p->planeY * cos(-ROT_SPEED);
	}
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_W)
		game->keys.key_w = 1;
	if (key == KEY_S)
		game->keys.key_s = 1;
	if (key == KEY_D)
		game->keys.key_d = 1;
	if (key == KEY_A)
		game->keys.key_a = 1;
	if (key == KEY_LEFT)
		game->keys.key_left = 1;
	if (key == KEY_RIGHT)
		game->keys.key_right = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_W)
		game->keys.key_w = 0;
	if (key == KEY_S)
		game->keys.key_s = 0;
	if (key == KEY_D)
		game->keys.key_d = 0;
	if (key == KEY_A)
		game->keys.key_a = 0;
	if (key == KEY_LEFT)
		game->keys.key_left = 0;
	if (key == KEY_RIGHT)
		game->keys.key_right = 0;
	return (0);
}
