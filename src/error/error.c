/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 03:49:13 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/19 18:49:20 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

int	p_err(char *msg, int ret)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

void	exit_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	free_int_array(int **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_texture_array(int **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
}
