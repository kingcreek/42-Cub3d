/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:18:23 by imurugar          #+#    #+#             */
/*   Updated: 2023/06/01 20:35:25 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_x_mouse(t_game *game, int mouse_x)
{
	double		old_dir_x;
	double		old_plane_x;
	static int	prev_mouse_x;
	int			mouse_x_diff;

	mouse_x_diff = mouse_x - prev_mouse_x;
	if (mouse_x_diff != 0)
	{
		prev_mouse_x = mouse_x;
		old_dir_x = game->player.dir_x;
		old_plane_x = game->player.plane_x;
		if (mouse_x_diff > 0)
		{
			game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
			game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
			game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
			game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
		}
		else if (mouse_x_diff < 0)
		{
			game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
			game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);
			game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
			game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
		}
	}
}

void update_with_cursor(t_game *game)
{
	int mouse_x;
    int mouse_y;

    mlx_mouse_get_pos(game->mlx, game->win, &mouse_x, &mouse_y);
	process_x_mouse(game, mouse_x);
}
