/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alialawlaqi <alialawlaqi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:24:44 by alialawlaqi       #+#    #+#             */
/*   Updated: 2023/02/06 13:43:50 by alialawlaqi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Use ft_strjoin to join the buffer content to the new line then free the old line
char	*ft_join_and_free(char *line, char *buffer)
{
	char	*updatedline;

	 updatedline = ft_strjoin(line, buffer);
	free(line);
	return (updatedline);
}

// check whiten the buffer if there is new lines to read
char	*ft_next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;

	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;

	while (buffer[i])
		line[j++] = buffer[i++];

	free(buffer);
	return (line);
}

char	*ft_get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	// if there is no line return null
	if (!buffer[i])
		return (NULL);
	// move to the end of line
	while (buffer[i] && buffer[i] != '\n')
		i++;

	line = ft_calloc(i + 2, sizeof(char));
	i = 0;

	// while not enl/eof and not newline copy buffer to line
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}

// if not eol and newline copy buffer to line

	if (buffer[i] && buffer[i] == '\n')
		line[i] = buffer[i];
	return (line);
}

// keep Readig a buffer size of the file untill \n or eof and store in a line
char	*ft_read_buffer_fromFD(int fd, char *line)
{
	char	*buff;
	int		rd_bytes;

	if (!line)
		line = ft_calloc(1, 1);

	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;

	while (!ft_strchr(line,'\n') && rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = 0;
		line = ft_join_and_free(line, buff);
	}
	free(buff);
	return (line);
}


char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd,0,0) < 0)
		return (0);
	buffer = ft_read_buffer_fromFD(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_next_line(buffer);
	return (line);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test1.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.pdf", O_RDONLY);
	i = 1;
	while (i < 6)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
*/
