/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 06:58:00 by imurugar          #+#    #+#             */
/*   Updated: 2023/06/01 13:44:09 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_content(char *map_file, t_parse *data, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit_error("Error:\nCan not open map file");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (contains_valid_objects(line, data) == true)
		{
			free(line);
			break ;
		}
		data->reading_pos++;
		free(line);
		line = get_next_line(fd);
	}
	if (line == NULL)
		exit_error("Error:\nMissing Attributes");
	get_map_length(fd, map_file, data);
	if (map_validathor(map_file, data, fd, game) == false
		|| data->error == true)
		exit_error("Error:\nInvalid Map");
	return (close(fd), true);
}

static void	process_position(t_game *game, char **map, int x, int y)
{
	if (ft_strchr("S", map[y][x]) != NULL)
		game->player.dir_y = 1;
	else if (ft_strchr("E", map[y][x]) != NULL)
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (ft_strchr("W", map[y][x]) != NULL)
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	game->player.plane_x = game->player.dir_y * 0.66;
	game->player.plane_y = -game->player.dir_x * 0.66;
}

void	get_player_pos(char **map, t_game *game)
{
	int		y;
	int		x;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\n' && map[y][x] != '\0')
		{
			if (ft_strchr("NESW", map[y][x]) != NULL)
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				game->player.dir_x = 0;
				game->player.dir_y = -1;
				process_position(game, map, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	map_checks(t_parse *data, int i, t_game *game)
{
	int	pos;
	int	flag;

	pos = 0;
	flag = 0;
	data->raw_map[i] = NULL;
	if (map_has_multiple_players_or_none(' ', 'Y') == true)
		return (false);
	get_player_pos(data->raw_map, game);
	while (data->raw_map[pos])
	{
		if (data->raw_map[pos][0] == '\n')
		{
			flag = 1;
		}
		else if (data->raw_map[pos][0] != '\n'
				&& data->raw_map[pos][0] != '\0' && flag)
		{
			exit_error("Error:\nMap contains invalid line");
		}
		pos++;
	}
	game->map.map = data->raw_map;
	return (true);
}

int	check_duplicate(char *line, t_parse *data)
{
	if ((ft_strncmp(line, "NO .", 4) == 0 && ft_strcmp(data->no, "X") != false)
		|| (ft_strncmp(line, "SO .", 4) == 0
			&& ft_strcmp(data->so, "X") != false)
		|| (ft_strncmp(line, "WE .", 4) == 0
			&& ft_strcmp(data->we, "X") != false)
		|| (ft_strncmp(line, "EA .", 4) == 0
			&& ft_strcmp(data->ea, "X") != false)
		|| (ft_strncmp(line, "F ", 2) == 0) && data->f_color[0] != -1
		|| (ft_strncmp(line, "C ", 2) == 0) && data->c_color[0] != -1)
		exit_error("Error:\nDuplicate map parameter");
	return (false);
}
