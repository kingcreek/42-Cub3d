/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:30:44 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/29 22:45:00 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

/*
int	worldMap[mapWidth][mapHeight] =
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
									};
									*/

void	draw(t_game *game)
{
	for (int y = 0; y < W_HEIGH; y++)
	{
		for (int x = 0; x < W_WIDTH; x++)
		{
			game->img.data[y * W_WIDTH + x] = game->zbuffer[y][x];
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void update_with_cursor(t_game *game)
{
    int mouseX;
    int mouseY;
    double oldDirX;
    double oldPlaneX;
    
    mlx_mouse_get_pos(game->mlx, game->win, &mouseX, &mouseY);
    
    static int prevMouseX = W_WIDTH / 2; // Posición anterior del mouse en X
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
}
/*
void process_mouse_movement(t_game *game, int mouseXDiff, int mouseYDiff)
{
	// Modificar los valores de dirección y plano según los desplazamientos del mouse
	double rotationSpeed = 0.01; // Velocidad de rotación del mouse (ajusta según tus necesidades)

	double oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(rotationSpeed * mouseXDiff) - game->player.dirY * sin(rotationSpeed * mouseXDiff);
	game->player.dirY = oldDirX * sin(rotationSpeed * mouseXDiff) + game->player.dirY * cos(rotationSpeed * mouseXDiff);

	double oldPlaneX = game->player.planeX;
	game->player.planeX = game->player.planeX * cos(rotationSpeed * mouseYDiff) - game->player.planeY * sin(rotationSpeed * mouseYDiff);
	game->player.planeY = oldPlaneX * sin(rotationSpeed * mouseYDiff) + game->player.planeY * cos(rotationSpeed * mouseYDiff);
}

int handle_mouse_movement(int x, int y, t_game *game)
{
	static int lastMouseX = 0;
	static int lastMouseY = 0;

	int mouseXDiff = x - lastMouseX;
	int mouseYDiff = y - lastMouseY;

	lastMouseX = x;
	lastMouseY = y;

	process_mouse_movement(game, mouseXDiff, mouseYDiff);

	return 0;
}
*/

void	calc(t_game *game)
{
	update_with_cursor(game);
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

static bool	arg_check(int argc, char **argv)
{
    char *error;
    
    error = NULL;
    if(argc != 2)
        error = "Error: too many arguments\n";
    else
        if(ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
            error = "Error: invalid file extension\n";
    if (error)
    {
        write(2, error, ft_strlen(error));
        return (false);
    }
    return (true);
}

static void	init_player(t_game *game)
{
	//game->player.posX = 22.0;
	//game->player.posY = 11.5;
	game->player.dirX = -1.0;
	game->player.dirY = 0.0;
	game->player.planeX = 0.0;
	game->player.planeY = 0.66;
}

static void	init_keys(t_game *game)
{
	game->keys.key_w = 0;
	game->keys.key_a = 0;
	game->keys.key_s = 0;
	game->keys.key_d = 0;
	game->keys.key_left = 0;
	game->keys.key_right = 0;
}

void	init_zbuffer(t_game *game)
{
	int i;
	
	game->zbuffer = (int**)ft_calloc(W_HEIGH, sizeof(int*));
    if (game->zbuffer == NULL)
		exit_error("Error while init zbuffer");
    i = 0;
    while (i < W_HEIGH) {
        game->zbuffer[i] = (int*)ft_calloc(W_WIDTH, sizeof(int));
        if (game->zbuffer[i] == NULL)
			exit_error("Error while init zbuffer");
        i++;
    }
}

int	exit_game(t_game *game)
{
	(void)game;
	exit (0);
}

int	main(int argc, char **argv)
{
	t_game game;
	
	if (argc != 2)
	{
		error("Please, add a map when launch the game: ./cub3d <map.cub>");
		return (EXIT_FAILURE);
	}
	game.mlx = mlx_init();
	//read_map_file(argv[1], &game);
	parse_file(argv[1], &game);
	//ft_print_2d_char_array(game.map.map);
	//printf("\n");
	init_zbuffer(&game);
	init_player(&game);
	init_keys(&game);
	//init_images(&game);

	
	
	game.win = mlx_new_window(game.mlx, W_WIDTH, W_HEIGH, "Cub3D");

	game.img.img = mlx_new_image(game.mlx, W_WIDTH, W_HEIGH);
	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);

	mlx_loop_hook(game.mlx, &main_loop, &game);
	//mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);

	mlx_mouse_hide(game.mlx, game.win);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	//mlx_hook(game.win, 6, (1L<<6), handle_mouse_movement, &game);

	mlx_loop(game.mlx);
}
