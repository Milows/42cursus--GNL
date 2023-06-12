/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micabrer <micabrer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:52:56 by micabrer          #+#    #+#             */
/*   Updated: 2023/06/12 13:48:51 by micabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_save_data(int fd, char *saved_data)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(saved_data, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		saved_data = ft_strjoin(saved_data, buffer);
	}
	free(buffer);
	return (saved_data);
}

char	*extract_line(char *saved_data)
{
	int		i;
	char	*line;

	i = 0;
	if (!saved_data[i])
		return (NULL);
	while (saved_data[i] && saved_data[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (saved_data[i] && saved_data[i] != '\n')
	{
		line[i] = saved_data[i];
		i++;
	}
	if (saved_data[i] == '\n')
	{
		line[i] = saved_data[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*extract_remaining(char *saved_data)
{
	int		i;
	int		j;
	char	*remaining;

	i = 0;
	while (saved_data[i] && saved_data[i] != '\n')
		i++;
	if (!saved_data[i])
	{
		free(saved_data);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * (ft_strlen(saved_data) - i + 1));
	if (!remaining)
		return (NULL);
	i++;
	j = 0;
	while (saved_data[i])
		remaining[j++] = saved_data[i++];
	remaining[j] = '\0';
	free(saved_data);
	return (remaining);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved_data[257];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	saved_data[fd] = read_save_data(fd, saved_data[fd]);
	if (!saved_data[fd])
		return (NULL);
	line = extract_line(saved_data[fd]);
	saved_data[fd] = extract_remaining(saved_data[fd]);
	return (line);
}
