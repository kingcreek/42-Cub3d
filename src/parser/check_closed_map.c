/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:20:26 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/18 20:15:01 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_inside_map(int x, int y, char **map, int size)
{
	if (y < 0 || y >= size)
		return (false);
	return (x >= 0 && x <= (int)ft_strlen(map[y]) - 1);
}

static bool	is_closed_map(int x, int y, char **map, int size)
{
	bool	closed;

	if (!is_inside_map(x, y, map, size))
		return (false);
	if (map[y][x] == '1' || map[y][x] == ' ')
		return (true);
	map[y][x] = '1';
	closed = true;
	closed &= is_closed_map(x, y - 1, map, size);
	closed &= is_closed_map(x, y + 1, map, size);
	closed &= is_closed_map(x - 1, y, map, size);
	closed &= is_closed_map(x + 1, y, map, size);
	return (closed);
}

bool	check_closed_map(char **map, int size)
{
	int	player[2];
	int	x_y[2];

	player[0] = -1;
	player[1] = -1;
	x_y[0] = 0;
	x_y[1] = 0;
	while (x_y[0] < size && player[0] == -1)
	{
		x_y[1] = 0;
		while (x_y[1] < (int)ft_strlen(map[x_y[0]]) && player[0] == -1)
		{
			if (map[x_y[0]][x_y[1]] == 'S' || map[x_y[0]][x_y[1]] == 'N' ||
				map[x_y[0]][x_y[1]] == 'E' || map[x_y[0]][x_y[1]] == 'W')
			{
					player[0] = x_y[1];
					player[1] = x_y[0];
			}
			x_y[1]++;
		}
		x_y[0]++;
	}
	if (player[0] == -1)
		return (false);
	return (is_closed_map(player[0], player[1], map, size));
}
