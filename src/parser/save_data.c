/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 06:58:16 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/25 07:01:45 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_texture_to_data(char *file, t_parse *data, char option)
{
	if (option == 'N')
	{
		free(data->no);
		data->no = ft_strdup(file);
	}
	if (option == 'S')
	{
		free(data->so);
		data->so = ft_strdup(file);
	}
	if (option == 'W')
	{
		free(data->we);
		data->we = ft_strdup(file);
	}
	if (option == 'E')
	{
		free(data->ea);
		data->ea = ft_strdup(file);
	}
	free(file);
}

void	save_color_to_data(char **rgb, t_parse *data, char option)
{
	if (option == 'F')
	{
		data->f_color[0] = ft_atoi(rgb[0]);
		data->f_color[1] = ft_atoi(rgb[1]);
		data->f_color[2] = ft_atoi(rgb[2]);
	}
	else if (option == 'C')
	{
		data->c_color[0] = ft_atoi(rgb[0]);
		data->c_color[1] = ft_atoi(rgb[1]);
		data->c_color[2] = ft_atoi(rgb[2]);
	}
	free_char_array(rgb);
}
