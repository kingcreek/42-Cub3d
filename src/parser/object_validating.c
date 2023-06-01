/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_validating.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 06:58:09 by imurugar          #+#    #+#             */
/*   Updated: 2023/06/01 17:11:18 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
int	contains_valid_objects(char *line, t_parse *data)
{
	if (invalid_attribute(line) == true)
		return (false);
	if (is_duplicate(line, data) == true)
		return (false);
	if (ft_strncmp(line, "NO .", 4) == 0
		|| ft_strncmp(line, "SO .", 4) == 0
		|| ft_strncmp(line, "WE .", 4) == 0
		|| ft_strncmp(line, "EA .", 4) == 0)
		if (validate_texture(line, data) == false)
			return (false);
	if ((ft_strncmp(line, "F ", 2) == 0 && ft_isdigit(line[2]) == true)
		|| (ft_strncmp(line, "C ", 2) == 0 && ft_isdigit(line[2]) == true))
		if (validate_color(line, data) == false)
			return (false);
	if (ft_strcmp(data->no, "X") == false
		&& ft_strcmp(data->so, "X") == false
		&& ft_strcmp(data->we, "X") == false
		&& ft_strcmp(data->ea, "X") == false
		&& data->f_color[0] != -1 && data->c_color[0] != -1)
		return (true);
	else
		return (false);
}
*/

int	contains_valid_objects(char *line, t_parse *data)
{
	if (ft_strcmp(data->no, "X") != false
		&& ft_strcmp(data->so, "X") != false
		&& ft_strcmp(data->we, "X") != false
		&& ft_strcmp(data->ea, "X") != false
		&& data->f_color[0] != -1 && data->c_color[0] != -1)
		return (true);
	if (invalid_attribute(line) == true)
		return (false);
	if (check_duplicate(line, data) == true)
		return (false);
	if (ft_strncmp(line, "NO .", 4) == 0
		|| ft_strncmp(line, "SO .", 4) == 0
		|| ft_strncmp(line, "WE .", 4) == 0
		|| ft_strncmp(line, "EA .", 4) == 0)
		if (validate_texture(line, data) == false)
			return (false);
	if ((ft_strncmp(line, "F ", 2) == 0 && ft_isdigit(line[2]) == true)
		|| (ft_strncmp(line, "C ", 2) == 0 && ft_isdigit(line[2]) == true))
	{
		if (validate_color(line, data) == false)
			return (false);
	}
	else
		return (false);
	return (false);
}

int	invalid_attribute(char *line)
{
	int	flag;

	flag = 0;
	if (line[0] != '\n' && line[3] != ' '
		&& line[4] != '.' && line[5] != '/'
		&& ft_strncmp(line, "NO", 2) != 0
		&& ft_strncmp(line, "SO", 2) != 0
		&& ft_strncmp(line, "WE", 2) != 0
		&& ft_strncmp(line, "EA", 2) != 0
		&& ft_strncmp(line, "F", 1) != 0
		&& ft_strncmp(line, "C", 1) != 0)
		flag++;
	if (flag != 0)
		exit_error("Error:\nWrong attributes");
	return (false);
}

int	validate_texture(char *line, t_parse *data)
{
	if (validate_no_so(line, data) == false
		|| validate_we_ea(line, data) == false)
		return (false);
	return (true);
}

int	validate_no_so(char *line, t_parse *data)
{
	char	*file;

	if (ft_strncmp(line, "NO", 2) == 0)
	{
		file = ft_strtrim(line, "NO \n");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'N');
		else
			return (free(file), false);
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		file = ft_strtrim(line, "SO \n");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'S');
		else
			return (free(file), false);
	}
	return (true);
}

int	validate_we_ea(char *line, t_parse *data)
{
	char	*file;

	if (ft_strncmp(line, "WE", 2) == 0)
	{
		file = ft_strtrim(line, "WE \n");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'W');
		else
			return (free(file), false);
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		file = ft_strtrim(line, "EA \n");
		if (it_can_be_opened(file) == true)
			save_texture_to_data(file, data, 'E');
		else
			return (free(file), false);
	}
	return (true);
}
