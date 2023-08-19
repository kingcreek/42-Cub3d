/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:05:06 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/19 19:10:28 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_image(t_game *game, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	img->img = mlx_xpm_file_to_image(game->mlx, path,
			&img->img_width, &img->img_height);
	if (!img->img)
		exit_error("Error:\nBad texture");
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	if (!img->data || img->img_width != TEXWIDTH \
		|| img->img_height != TEXHEIGHT)
		exit_error("Error:\nBad texture");
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, img->img);
}

static bool	init_wall_img(t_game *game, t_parse *data)
{
	t_img	img;

	load_image(game, game->texture[0], data->so, &img);
	load_image(game, game->texture[1], data->no, &img);
	load_image(game, game->texture[2], data->we, &img);
	load_image(game, game->texture[3], data->ea, &img);
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	return (true);
}

static void	init_image_stack(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->texture = ft_calloc(5, sizeof(int *));
	if (!game->texture)
		exit_error("Malloc, failed");
	while (i < 4)
	{
		game->texture[i] = ft_calloc(TEXHEIGHT * TEXWIDTH + 1, sizeof(int));
		if (!game->texture[i++])
			exit_error("Malloc, failed");
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < TEXHEIGHT * TEXWIDTH)
		{
			game->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}

bool	init_images(t_game *game, t_parse *data)
{
	init_image_stack(game);
	if (!init_wall_img(game, data))
		return (false);
	return (true);
}
