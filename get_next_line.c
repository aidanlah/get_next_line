/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aileong <aileong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:26:26 by aileong           #+#    #+#             */
/*   Updated: 2024/07/11 14:26:29 by aileong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
// #include <stdio.h>
// #include <fcntl.h>

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str);
	left_str = ft_new_left_str(left_str);
	return (line);
}

/*int	main(void)
{
	char *line;
	int i;
	int fd1;
	int fd2;
	int fd3;

	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		perror("Error opening file");
		return 1;
	}

	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		if (line)
		{
			printf("line [%02d]: %s", i, line);
			free(line);
		}

		line = get_next_line(fd2);
		if (line)
		{
			printf("line [%02d]: %s", i, line);
			free(line);
		}

		line = get_next_line(fd3);
		if (line)
		{
			printf("line [%02d]: %s", i, line);
			free(line);
		}
		i++;
	}

	close(fd1);
	close(fd2);
	close(fd3);
	return 0;
}*/
