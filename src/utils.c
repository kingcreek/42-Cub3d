/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 04:13:37 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/19 19:55:57 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	commacounter(char *line)
{
	int	i;
	int	commacount;

	i = 0;
	commacount = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			commacount++;
		i++;
	}
	if (commacount != 2)
	{
		return (false);
	}
	return (true);
}

bool	arg_check(int argc, char **argv)
{
	char	*error;

	error = NULL;
	if (argc != 2)
		error = "Error:\nToo many arguments\n";
	else
		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
			error = "Error:\nInvalid file extension\n";
	if (error)
	{
		write(2, error, ft_strlen(error));
		return (false);
	}
	return (true);
}

void	init_zbuffer(t_game *game)
{
	int	i;

	game->zbuffer = (int **)ft_calloc(W_HEIGH + 1, sizeof(int *));
	if (game->zbuffer == NULL)
		exit_error("Error:\nWhile init zbuffer");
	game->zbuffer[W_HEIGH] = NULL;
	i = 0;
	while (i < W_HEIGH)
	{
		game->zbuffer[i] = (int *)ft_calloc(W_WIDTH, sizeof(int));
		if (game->zbuffer[i] == NULL)
			exit_error("Error:\nWhile init zbuffer");
		i++;
	}
}

void	init_vars(t_game *game)
{
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->keys.key_w = 0;
	game->keys.key_a = 0;
	game->keys.key_s = 0;
	game->keys.key_d = 0;
	game->keys.key_left = 0;
	game->keys.key_right = 0;
	game->map.map = NULL;
	game->zbuffer = NULL;
	game->texture = NULL;
}
