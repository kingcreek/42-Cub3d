/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:30:44 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/31 02:06:49 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < W_HEIGH)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			game->img.data[y * W_WIDTH + x] = game->zbuffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

/*
void update_with_cursor(t_game *game)
{
    int mouseX;
    int mouseY;
    double oldDirX;
    double oldPlaneX;
    
    mlx_mouse_get_pos(game->mlx, game->win, &mouseX, &mouseY);
    
    static int prevMouseX = W_WIDTH / 2;
    int mouseXDiff = mouseX - prevMouseX;
    
    if (mouseXDiff != 0)
    {
        prevMouseX = mouseX;
        
        if (mouseXDiff < 0)
        {
            oldDirX = game->player.dirX;
            game->player.dirX = game->player.dirX * cos(ROT_SPEED) - game->player.dirY * sin(ROT_SPEED);
            game->player.dirY = oldDirX * sin(ROT_SPEED) + game->player.dirY * cos(ROT_SPEED);
            oldPlaneX = game->player.planeX;
            game->player.planeX = game->player.planeX * cos(ROT_SPEED) - game->player.planeY * sin(ROT_SPEED);
            game->player.planeY = oldPlaneX * sin(ROT_SPEED) + game->player.planeY * cos(ROT_SPEED);
        }
        else if (mouseXDiff > 0)
        {
            oldDirX = game->player.dirX;
            game->player.dirX = game->player.dirX * cos(-ROT_SPEED) - game->player.dirY * sin(-ROT_SPEED);
            game->player.dirY = oldDirX * sin(-ROT_SPEED) + game->player.dirY * cos(-ROT_SPEED);
            oldPlaneX = game->player.planeX;
            game->player.planeX = game->player.planeX * cos(-ROT_SPEED) - game->player.planeY * sin(-ROT_SPEED);
            game->player.planeY = oldPlaneX * sin(-ROT_SPEED) + game->player.planeY * cos(-ROT_SPEED);
        }
    }
}*/
void	calc(t_game *game)
{
	//update_with_cursor(game);
	draw_floor_ceiling(game);
	draw_wall(game);
}

int	main_loop(t_game *game)
{
	calc(game);
	draw(game);
	process_ws_position(game, &game->player);
	process_ad_position(game, &game->player);
	process_angle(game, &game->player);
	return (0);
}

int	exit_game(t_game *game)
{
	(void)game;
	exit (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		error("Error:\nNo no no 😡, add map like: ./cub3d <map.cub>");
		return (EXIT_FAILURE);
	}
	game.mlx = mlx_init();
	init_vars(&game);
	parse_file(argv[1], &game);
	init_zbuffer(&game);
	game.win = mlx_new_window(game.mlx, W_WIDTH, W_HEIGH, "Cub3D");
	game.img.img = mlx_new_image(game.mlx, W_WIDTH, W_HEIGH);
	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, \
		&game.img.size_l, &game.img.endian);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_mouse_hide(game.mlx, game.win);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop(game.mlx);
}
