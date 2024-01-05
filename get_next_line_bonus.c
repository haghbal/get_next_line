/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haghbal <haghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:29:20 by haghbal           #+#    #+#             */
/*   Updated: 2024/01/05 16:16:42 by haghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line_buffer(char *buf, char *stable, int fd)
{
	int		n_byt;
	char	*tmp;

	n_byt = 1;
	while (n_byt != 0)
	{
		n_byt = read(fd, buf, BUFFER_SIZE);
		if (n_byt == -1)
		{
			free(stable);
			return (NULL);
		}
		else if (n_byt == 0)
			break ;
		buf[n_byt] = '\0';
		tmp = stable;
		stable = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(stable, '\n'))
			break ;
	}
	return (stable);
}

static char	*get_my_line(char *line)
{
	char	*le_reste;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (0);
	le_reste = ft_strdup(&line[i]);
	line[i] = '\0';
	return (le_reste);
}

char	*get_next_line(int fd)
{
	static char	*stable[MAX_FD];
	char		*line;
	char		*buffer;

	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = get_line_buffer(buffer, stable[fd], fd);
	free(buffer);
	buffer = NULL;
	if (!line)
	{
		stable[fd] = 0;
		return (NULL);
	}
	stable[fd] = get_my_line(line);
	return (line);
}
