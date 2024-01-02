/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haghbal <haghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:29:20 by haghbal           #+#    #+#             */
/*   Updated: 2024/01/02 17:43:41 by haghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line_buffer(char *buf, char **stable, int fd)
{
	int		n_byt;
	char	*tmp;

	n_byt = 1;
	while (n_byt != 0)
	{
		n_byt = read(fd, buf, BUFFER_SIZE);
		if (n_byt == -1)
		{
			free(*stable);
			*stable = NULL;
			return (NULL);
		}
		else if (n_byt == 0)
			break ;
		buf[n_byt] = '\0';
		tmp = *stable;
		*stable = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(*stable, '\n'))
			break ;
	}
	return (*stable);
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

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = get_line_buffer(buffer, &stable[fd], fd);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stable[fd] = get_my_line(line);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	char *line;
// 	int fd = open("exm.txt", O_RDONLY);
// 	// int fd1 = open("exm1.txt", O_RDONLY);
// 	// int fd2 = open("exm2.txt", O_RDONLY);
// 	int i = 1;
// 	while (i < 6)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		// line = 0;
// 		// line = get_next_line(fd1);
// 		// printf("%s", line);
// 		// line = 0;
// 		// line = get_next_line(fd2);
// 		// printf("%s", line);
// 		// line = 0;
// 		// line = get_next_line(fd);
// 		// printf("%s", line);
// 		// line = 0;
// 		// line = get_next_line(fd2);
// 		// printf("%s", line);
// 		free (line);
// 		i++;
// 	}
// }