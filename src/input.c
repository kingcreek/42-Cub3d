/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:14:36 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/19 18:47:42 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_ad_position(t_game *game, t_player *player)
{
	char	**map;

	map = game->map.map;
	if (game->keys.key_d)
	{
		if (ft_strchr("NESW0", map[(int)(player->pos_y + \
			player->dir_x * MOVE_SPEED)][(int)(player->pos_x)]) != NULL)
			player->pos_y += player->dir_x * MOVE_SPEED;
		if (ft_strchr("NESW0", map[(int)(player->pos_y)][(int)(player->pos_x - \
			player->dir_y * MOVE_SPEED)]) != NULL)
			player->pos_x -= player->dir_y * MOVE_SPEED;
	}
	if (game->keys.key_a)
	{
		if (ft_strchr("NESW0", map[(int)(player->pos_y - \
			player->dir_x * MOVE_SPEED)][(int)(player->pos_x)]) != NULL)
			player->pos_y -= player->dir_x * MOVE_SPEED;
		if (ft_strchr("NESW0", map[(int)(player->pos_y)][(int)(player->pos_x + \
			player->dir_y * MOVE_SPEED)]) != NULL)
			player->pos_x += player->dir_y * MOVE_SPEED;
	}
}

void	process_ws_position(t_game *game, t_player *player)
{
	char	**map;

	map = game->map.map;
	if (game->keys.key_w)
	{
		if (ft_strchr("NESW0", map[(int)(player->pos_y + \
			player->dir_y * MOVE_SPEED)][(int)(player->pos_x)]) != NULL)
			player->pos_y += player->dir_y * MOVE_SPEED;
		if (ft_strchr("NESW0", map[(int)(player->pos_y)][(int)(player->pos_x + \
			player->dir_x * MOVE_SPEED)]) != NULL)
			player->pos_x += player->dir_x * MOVE_SPEED;
	}
	if (game->keys.key_s)
	{
		if (ft_strchr("NESW0", map[(int)(player->pos_y - \
			player->dir_y * MOVE_SPEED)][(int)(player->pos_x)]) != NULL)
			player->pos_y -= player->dir_y * MOVE_SPEED;
		if (ft_strchr("NESW0", map[(int)(player->pos_y)][(int)(player->pos_x - \
			player->dir_x * MOVE_SPEED)]) != NULL)
			player->pos_x -= player->dir_x * MOVE_SPEED;
	}
}

void	process_angle(t_game *game, t_player *p)
{
	double	old_dirx;
	double	old_planex;

	if (game->keys.key_right)
	{
		old_dirx = p->dir_x;
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = old_dirx * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		old_planex = p->plane_x;
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = old_planex * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
	}
	else if (game->keys.key_left)
	{
		old_dirx = p->dir_x;
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = old_dirx * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		old_planex = p->plane_x;
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y
			* sin(-ROT_SPEED);
		p->plane_y = old_planex * sin(-ROT_SPEED) + p->plane_y
			* cos(-ROT_SPEED);
	}
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit_game(game);
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
