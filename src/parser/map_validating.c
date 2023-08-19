/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 06:58:04 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/19 22:36:40 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_validathor(t_parse *data, int fd, t_game *game)
{
	int			i;
	static int	k;
	char		*line;
	char		**tmp_map;

	line = get_next_line(fd);
	while (k++ != data->reading_pos)
		line = get_line(fd, line);
	while (line != NULL && line_cotains_only_spaces(line) == true)
		line = get_line(fd, line);
	data->raw_map = ft_calloc((data->map_length + 1), sizeof(char *));
	tmp_map = ft_calloc((data->map_length + 1), sizeof(char *));
	if (data->raw_map == NULL || tmp_map == NULL)
		exit_error("Error:\nMalloc failed");
	i = 0;
	while (line != NULL)
	{
		if (line_has_invalid_chars(line) == true)
			return (free_char_array(tmp_map), free(line), false);
		tmp_map[i] = ft_strdup(line);
		data->raw_map[i++] = copy_map_line_fixed(line, data);
		line = get_line(fd, line);
	}
	free(line);
	return (close(fd), perform_checks(data, game, i, tmp_map));
}

// skip lines with only space on them
void	get_map_length(int fd, char *map_file, t_parse *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && line_cotains_only_spaces(line) == true)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		if (ft_strlen(line) > data->line_size)
			data->line_size = ft_strlen(line);
		data->map_length++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		exit_error("Error:\nCan not open map file");
		exit(0);
	}
}

int	line_cotains_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'
			|| line[i] == '\r' || line[i] == '\f')
			i++;
		else
			return (false);
	}
	return (true);
}

int	line_has_invalid_chars(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (true);
	while (line[i] != '\n')
	{
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1'
			|| line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E')
		{
			if (map_has_multiple_players_or_none(line[i], 'N') == true)
				return (true);
			i++;
		}
		else if (line[i] == '\0')
			return (false);
		else
			exit_error("Error:\nInvalid caracter");
	}
	return (false);
}

int	map_has_multiple_players_or_none(char c, char option)
{
	static int	n = 0;
	static int	s = 0;
	static int	w = 0;
	static int	e = 0;

	if (c == 'N')
		n++;
	else if (c == 'S')
		s++;
	else if (c == 'W')
		w++;
	else if (c == 'E')
		e++;
	if (n > 1 || s > 1 || w > 1 || e > 1)
		exit_error("Error:\nDuplicate Player");
	if (option == 'Y')
	{
		if ((n + s + w + e) == 0)
			exit_error("Error:\nMissing Player");
		else if ((n + s + w + e) > 1)
			exit_error("Error:\nToo many players");
	}
	return (false);
}
