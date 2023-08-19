/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 06:47:54 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/19 22:17:30 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_color(char *line, t_parse *data)
{
	char	**rgb;

	if (commacounter(line) == false || rgb_contains_letters(line) == true
		|| has_duplicate_rgb(line) == true)
		return (false);
	if (line[0] == 'F')
	{
		rgb = split_rgb(line, " \n");
		if (valid_rgb(rgb) == true)
			save_color_to_data(rgb, data, 'F');
		else
			return (free_char_array(rgb), false);
	}
	if (line[0] == 'C')
	{
		rgb = split_rgb(line, " \n");
		if (valid_rgb(rgb) == true)
			save_color_to_data(rgb, data, 'C');
		else
			return (free_char_array(rgb), false);
	}
	return (true);
}

char	**split_rgb(char *line, char *trim_with)
{
	char	*trimmed_line;
	char	**rgb;

	trimmed_line = ft_strtrim(line + 1, trim_with);
	rgb = ft_split(trimmed_line, ',');
	free(trimmed_line);
	return (rgb);
}

int	has_duplicate_rgb(char *line)
{
	static int	f;
	static int	c;

	f = 0;
	c = 0;
	if (line[0] == 'F')
		f++;
	else if (line[0] == 'C')
		c++;
	else if (f != 1 || c != 1)
		exit_error("Error:\nRGB duplicate value");
	return (false);
}

int	valid_rgb(char **rgb)
{
	if (!is_only_digit(rgb[0]) || !is_only_digit(rgb[1]) \
		|| !is_only_digit(rgb[2]))
		exit_error("Error:\nInvalid RGB");
	if ((ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[0]) < 0)
		|| (ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[1]) < 0)
		|| (ft_atoi(rgb[2]) > 255 || ft_atoi(rgb[2]) < 0))
		exit_error("Error:\nRGB Out of range");
	return (true);
}

int	rgb_contains_letters(char *line)
{
	size_t	i;

	i = 2;
	while (i < ft_strlen(line) - 1)
	{
		if (line[i] == ' ' || line[i] == ',' || ft_isdigit(line[i]) == true)
			i++;
		else
			return (true);
	}
	return (false);
}
