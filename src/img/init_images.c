/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:05:06 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/29 21:47:03 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_image(t_game *game, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(game->mlx, img->img);
}

static bool	init_wall_img(t_game *game, t_parse *data)
{
	t_img	img;
	
	load_image(game, game->texture[0], data->no, &img);
	load_image(game, game->texture[1], data->so, &img);
	load_image(game, game->texture[2], data->ea, &img);
	load_image(game, game->texture[3], data->we, &img);
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
	if (!(game->texture = (int **)malloc(sizeof(int *) * 5)))
		exit_error("Malloc, failed");
	while(i < 5)
	{
		if (!(game->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			exit_error("Malloc, failed");
		i++;
	}
	i = 0;
	while(i < 5)
	{
		j = 0;
		while(j < texHeight * texWidth)
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