/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 04:13:37 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/27 16:22:33 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb(int r, int g, int b, int a) //uint32_t
{
	return (r << 24 | g << 16 | b << 8 | a);
}

char	*ft_strdup2(char *str, int start, int end)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (end - start + 1));
	if (result == NULL)
	{
		printf("MALLOC_FAIL");
		return (NULL);
	}
	i = -1;
	while (start + ++i != end)
		result[i] = str[i + start];
	result[i] = '\0';
	return (result);
}

int	commacounter(char *line)
{
	int	i;
	int	commacount;

	i = 0;
	commacount = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			commacount++;
		i++;
	}
	if (commacount != 2)
	{
		printf("%s", "COMMA");
		return (false);
	}
	return (true);
}

