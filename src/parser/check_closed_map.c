/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:07:45 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/31 14:52:38 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	all_line_are_closed(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] != '1' && line[pos] != ' ' && line[pos] != '\n')
			return (false);
		pos++;
	}
	if (line[pos - 2] != '1')
		return (false);
	return (true);
}

static bool	line_are_closed(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos] == ' ')
		pos++;
	if (line[pos] != '1')
		return (false);
	while (line[pos])
		pos++;
	if (line[pos - 2] != '1')
		return (false);
	return (true);
}

bool	check_line(char *line, int i, t_parse *data)
{
	if (i == 0)
		return (all_line_are_closed(line));
	else if (i == data->map_length)
		return (all_line_are_closed(line));
	else
		return (line_are_closed(line));
}
