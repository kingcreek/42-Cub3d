/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 07:45:25 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/30 14:00:29 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parse_data(t_parse *data)
{
	data->raw_map = NULL;
	data->no = ft_strdup("X");
	data->so = ft_strdup("X");
	data->we = ft_strdup("X");
	data->ea = ft_strdup("X");
	data->f_color[0] = -1;
	data->f_color[1] = -1;
	data->f_color[2] = -1;
	data->c_color[0] = -1;
	data->c_color[1] = -1;
	data->c_color[2] = -1;
	data->reading_pos = 0;
	data->map_length = 0;
	data->line_size = 0;
}

void	ft_print_2d_char_array(char **array_2d)
{
	int	i;
	int	k;

	if (array_2d == NULL)
		return ;
	i = 0;
	while (array_2d[i] != NULL)
	{
		k = 0;
		while (array_2d[i][k] != '\0')
		{
			ft_putchar_fd(array_2d[i][k], 1);
			k++;
		}
		write(1, "\n", 2);
		i++;
	}
}

static int	convert_color(int r, int g, int b)
{
	int	color;

	color = 0;
	color |= (r & 0xFF) << 16;
	color |= (g & 0xFF) << 8;
	color |= (b & 0xFF);
	return (color);
}

void	parse_file(char *argv, t_game *game)
{
	t_parse	data;

	init_parse_data(&data);
	input_check(argv, &data, game);
	init_images(game, &data);
	game->map.ceil_color = convert_color(data.c_color[0], \
		data.c_color[1], data.c_color[2]);
	game->map.floor_color = convert_color(data.f_color[0], \
		data.f_color[1], data.f_color[2]);
}
