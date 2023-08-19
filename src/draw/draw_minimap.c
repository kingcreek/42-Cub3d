/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:25:01 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/18 20:25:03 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_map(t_game *game, int color, int x, int y)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < MINIMAP_SCALE)
	{
		dx = 0;
		while (dx < MINIMAP_SCALE)
		{
			game->zbuffer[(y * MINIMAP_SCALE) + dy] \
			[(x * MINIMAP_SCALE) + dx] = color;
			dx++;
		}
		dy++;
	}
}

static void	draw_map(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (game->map.map[y] != NULL)
	{
		x = 0;
		while (game->map.map[y][x] != '\0')
		{
			color = 0;
			if (ft_strchr("NESW0", game->map.map[y][x]))
				color = 0xFFFFFF;
			fill_map(game, color, x, y);
			x++;
		}
		y++;
	}
}

static void	draw_player(t_game *game)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	x = (int)(game->player.pos_x * MINIMAP_SCALE);
	y = (int)(game->player.pos_y * MINIMAP_SCALE);
	x -= PLAYER_SIZE / 2;
	y -= PLAYER_SIZE / 2;
	dy = 0;
	while (dy < PLAYER_SIZE)
	{
		dx = 0;
		while (dx < PLAYER_SIZE)
		{
			game->zbuffer[y + dy][x + dx] = PLAYER_COLOR;
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_game *game)
{
	draw_map(game);
	draw_player(game);
}
