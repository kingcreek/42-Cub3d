/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 06:58:21 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/31 13:27:05 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_line(int fd, char *line)
{
	free(line);
	return (get_next_line(fd));
}

char	*copy_map_line(char *content)
{
	int		i;
	int		content_len;
	char	*line;

	i = -1;
	content_len = ft_strlen(content) + 1;
	line = malloc(sizeof(char) * content_len);
	if (line == NULL)
		exit_error("Error:\nMalloc failed");
	while (content[++i] != '\0')
		line[i] = content[i];
	line[i] = '\0';
	return (line);
}

char	*copy_map_line_fixed(char *content, t_parse *data)
{
	int		i;
	int		content_len;
	char	*line;

	i = -1;
	content_len = data->line_size;
	line = malloc(sizeof(char) * content_len);
	if (line == NULL)
		exit_error("Error:\nMalloc failed");
	while (content[++i] != '\0')
	{
		line[i] = content[i];
		if (content[i] == ' ')
			line[i] = '1';
	}
	while (i < content_len)
	{
		line[i - 1] = '1';
		i++;
	}
	line[content_len - 1] = '\0';
	return (line);
}

// void	ft_print_2d_char_array(char **array_2d)
// {
// 	int	i;
// 	int	k;

// 	if (array_2d == NULL)
// 		return ;
// 	i = 0;
// 	while (array_2d[i] != NULL)
// 	{
// 		k = 0;
// 		while (array_2d[i][k] != '\0')
// 		{
// 			put_chars(array_2d[i][k]);
// 			k++;
// 		}
// 		write(1, "\n", 2);
// 		i++;
// 	}
// }

void	free_char_array(char **array)
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

int	it_can_be_opened(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		exit_error("Error: Can not open file");
		return (false);
	}
	close(fd);
	return (true);
}
