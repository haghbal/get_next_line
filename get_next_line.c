/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haghbal <haghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:12:08 by haghbal           #+#    #+#             */
/*   Updated: 2024/01/05 17:05:39 by haghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line_buffer(int fd, char *recall, char *buf)
{
	int		n_byt;
	char	*tmp;

	n_byt = 1;
	while (n_byt != 0)
	{
		n_byt = read(fd, buf, BUFFER_SIZE);
		if (n_byt == -1)
		{
			free(recall);
			return (NULL);
		}
		else if (n_byt == 0)
			break ;
		buf[n_byt] = '\0';
		tmp = recall;
		recall = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(recall, '\n'))
			break ;
	}
	return (recall);
}

static char	*get_my_line(char *line)
{
	char	*recall;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (0);
	recall = ft_strdup(&line[i]);
	line[i] = '\0';
	return (recall);
}

char	*get_next_line(int fd)
{
	static char	*recall;
	char		*line;
	char		*buf;

	buf = malloc((sizeof(char) * ((size_t)BUFFER_SIZE + 1)));
	if (!buf)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buf);
		buf = (NULL);
		return (NULL);
	}
	line = get_line_buffer(fd, recall, buf);
	free (buf);
	buf = NULL;
	if (line == NULL)
	{
		recall = 0;
		return (NULL);
	}
	recall = get_my_line(line);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
	int i = 0;
	while (i < 4)
	{
		printf("%s", line);
		line = get_next_line(fd);
		free(line);
		i++;
	}
}