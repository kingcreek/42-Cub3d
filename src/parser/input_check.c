/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 06:58:00 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/29 22:13:00 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	input_check(char *argv, t_parse *data, t_game *game)
{
	int	i;

	i = ft_strlen(argv);
	if (argv && i > 3 && argv[i - 1] == 'b' && argv[i - 2] == 'u'
		&& argv[i - 3] == 'c' && argv[i - 4] == '.')
	{
		if (validate_content(argv, data, game) == false)
			return (false);
	}
	else
		exit_error("Wrong file extension");
	return (true);
}

int	validate_content(char *map_file, t_parse *data, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit_error("Error: Can not open map file");
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
		exit_error("Error: Missing Attributes");
	get_map_length(fd, map_file, data);
	if (map_validathor(map_file, data, fd, game) == false || data->error == true)
		exit_error("Error: Invalid Map");
	return (close(fd), true);
}

void	get_player_pos(char **map, t_game *game)
{
	int		y;
	int		x;
	double	plane_length;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\n' && map[y][x] != '\0')
		{
			if (ft_strchr("NESW", map[y][x]) != NULL)
			{
				game->player.posX = x + 0.5;
				game->player.posY = y + 0.5;
				if (ft_strchr("N", map[y][x]) != NULL)
					game->player.dirX = 1;
				return ;
			}
			x++;
		}
		y++;
	}
}

// TO PRINT MAP
	// print_map_objects(data);
	// ft_print_2d_char_array(data->map_copy);
	// ft_printf("\n");
int	map_checks(t_parse *data, int i, t_game *game)
{
	data->raw_map[i] = NULL;
	if (map_has_multiple_players_or_none(' ', 'Y') == true)
		return (false);
	//data->map_copy = copy_2d_char_array(data->raw_map);
	get_player_pos(data->raw_map, game);
	game->map.map = data->raw_map;
	
	
	//dfs(data->map_copy, y, x, data);
	//free_char_array(data->map_copy);
	/*if (data->error == true)
	{
		free_char_array(data->raw_map);
		return (false);
	}*/
	//data->map_copy = NULL;
	//if (data->error == true)
	//	return (false);
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
		exit_error("Error: Duplicate map parameter");
	return (false);
	/*
	if ((ft_strncmp(line, "NO .", 4) == 0 && ft_strcmp(data->no, "X") == false)
		|| (ft_strncmp(line, "SO .", 4) == 0
			&& ft_strcmp(data->so, "X") == false)
		|| (ft_strncmp(line, "WE .", 4) == 0
			&& ft_strcmp(data->we, "X") == false)
		|| (ft_strncmp(line, "EA .", 4) == 0
			&& ft_strcmp(data->ea, "X") == false)
		|| (ft_strncmp(line, "F ", 2) == 0) && data->f_color[0] != -1
		|| (ft_strncmp(line, "C ", 2) == 0) && data->c_color[0] != -1)
		return (error("DUPLICATE\n"), true);
	return (false);*/
}

// char	put_chars(char c)
// {
// 	char	colored_0[] = "\e[1;37m0\e[0m";
// 	char	colored_1[] = "\e[1;31m1\e[0m";
// 	char	colored_e[] = "\e[1;33mE\e[0m";
// 	char	colored_s[] = "\e[1;32mS\e[0m";
// 	char	colored_w[] = "\e[1;35mW\e[0m";
// 	char	colored_n[] = "\e[1;34mN\e[0m";
// 	char	colored_x[] = "\e[1;34mX\e[0m";
// 	char	colored_plus[] = "\e[1;34m+\e[0m";
// 	char	colored_v[] = "\e[1;33mV\e[0m";

// 	if (c == '0')
// 		write(1, &colored_0, 13);
// 	else if (c == '1')
// 		write(1, &colored_1, 13);
// 	else if (c == 'N')
// 		write(1, &colored_n, 13);
// 	else if (c == 'S')
// 		write(1, &colored_s, 13);
// 	else if (c == 'W')
// 		write(1, &colored_w, 13);
// 	else if (c == 'E')
// 		write(1, &colored_e, 13);
// 	else if (c == '+')
// 		write(1, &colored_plus, 13);
// 	else if (c == 'V')
// 		write(1, &colored_v, 13);
// 	else if (c == 'X')
// 		write(1, &colored_x, 13);
// 	else if (c == ' ')
// 		write(1, " ", 1);
// 	return (0);
// }
