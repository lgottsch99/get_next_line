/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:52:10 by lgottsch          #+#    #+#             */
/*   Updated: 2024/10/09 20:26:05 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>

/*
check max no fds?

fix freeing if read ret -1 between calls

*/

//use double pointer so u can operate on static pointer
char	*get_nl_and_update(char	**leftover)
{
	int		index;
	char	*newline;
	char	*updated;

	index = getindexnl(*leftover);
	newline = ft_substr(*leftover, 0, index + 1);
	if (!newline)
		return (NULL);
	updated = ft_substr(*leftover, index + 1, ft_strlen(*leftover));
	free(*leftover);
	*leftover = NULL;
	if (!updated)
		return (NULL);
	else
		*leftover = updated;
	return (newline);
}

int	is_nl(char *new)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(new))
	{
		if (new[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*make_new(char **leftover, char *buf)
{
	char	*new;

	if (*leftover)
	{
		new = ft_strjoin(*leftover, buf);
		free(*leftover);
		*leftover = NULL;
		if (!new)
			return (NULL);
	}
	else
	{
		new = ft_strdup(buf);
		if (!new)
			return (NULL);
	}
	return (new);
}

char	*read_until_nl(int fd, char *buf, char **leftover)
{
	char	*new;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*leftover);
			*leftover = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		new = make_new(leftover, buf);
		if (!new)
			return (NULL);
		*leftover = new;
		new = NULL;
		if (is_nl(*leftover))
			break ;
	}
	return (*leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buf;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	leftover = read_until_nl(fd, buf, &leftover);
	free(buf);
	buf = NULL;
	if (!leftover)
	{
		free(buf);
		return (NULL);
	}
	newline = get_nl_and_update(&leftover);
	if (!leftover || ft_strlen(leftover) == 0)
	{
		free (leftover);
		leftover = NULL;
	}
	return (newline);
}

/*
read and create string until \n (use strjoin, free old leftover)
extract new line, shorten leftover
free buf
return new line

*/

// int main (void)
// {
// 	//use open to open file and get fd
// 	char	*filename = "sample.txt";
// 	char	*newline;

// 	//read from file
// 	int	fd = open(filename, O_RDONLY);
// 	if (fd == -1)//open returns -1 on error
// 	{
// 		printf("error opening file\n");
// 		return (1);
// 	}
// 	//print  lines
// 	for (int i = 0; i < 10; i++)
// 	{
// 		newline = get_next_line(fd);
// 		printf("newline: %s\n", newline);
// 		free(newline);
// 		newline = NULL;
// 	close(fd);

	

// 	}

// 	//read from stdin (terminal)

// 	// for (int i = 0; i < 9; i++)
// 	// {
// 	// 	newline = get_next_line(0);
// //  	printf("newline: %s\n", newline);
// 	// }

// 	close(fd);
// 	return (0);
// }