/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:30:44 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/19 22:19:13 by imurugar         ###   ########.fr       */
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

void	calc(t_game *game)
{
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
	if (game->map.map)
		free_char_array(game->map.map);
	if (game->zbuffer)
		free_int_array(game->zbuffer);
	if (game->texture)
		free_int_array(game->texture);
	mlx_destroy_image(game->mlx, game->img.img);
	exit (0);
}
/*void leaks()
{
	system("leaks -q cub3D");
}*/
//atexit(leaks);

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
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_hook(game.win, 2, 0L, key_press, &game);
	mlx_hook(game.win, 3, 0L, key_release, &game);
	mlx_loop(game.mlx);
}
