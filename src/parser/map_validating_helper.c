/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validating_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:25:03 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/19 22:47:55 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_only_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static bool	check_map_size(char **tmp_map)
{
	int	pos;

	pos = 0;
	while (tmp_map[pos])
	{
		if (ft_strlen(tmp_map[pos]) > 40)
			return (false);
		if (pos >= 20)
			return (false);
		pos++;
	}
	return (true);
}

bool	perform_checks(t_parse *data, t_game *game, int i, char **tmp_map)
{
	tmp_map[i] = NULL;
	if (!check_map_size(tmp_map))
	{
		free_char_array(tmp_map);
		return (false);
	}
	if (map_checks(data, i, game) == false)
	{
		free_char_array(tmp_map);
		return (false);
	}
	if (!check_closed_map(tmp_map, data->map_length))
	{
		free_char_array(tmp_map);
		return (false);
	}
	if (tmp_map[i - 1][0] == '\0' || tmp_map[i - 1][0] == '\n')
	{
		free_char_array(tmp_map);
		return (false);
	}
	free_char_array(tmp_map);
	return (true);
}
