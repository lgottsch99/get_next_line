/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:52:10 by lgottsch          #+#    #+#             */
/*   Updated: 2024/10/08 20:45:14 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>


/*
check max no fds?

ok	empty file?
OK 	EOF? need to set leftover to null 

no nl in file?
memleaks??
BUfsize 1 double free?

OK 	stdin

*/

char	*update(char *leftover)
{
	int index;
	char	*updated;

	index = getindexnl(leftover);
	updated = ft_substr(leftover, index + 1, ft_strlen(leftover));
	//printf("updated: %s\n", updated);
	
	free(leftover);
	leftover = NULL;
	return (updated);

	//count how much after nl
	//substr rest

}

char	*get_nl(char *leftover)
{
	int		index;
	char	*newline;

	//extract nl, count until nl
	index = getindexnl(leftover);
	//printf("index nl: %i\n", index);

	newline = ft_substr(leftover, 0, index + 1);

	return (newline);
}

int	is_nl(char *new)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(new))
	{
		if (new[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_until_nl(int fd, char *buf, char *leftover)
{
	char	*new;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		//read into buf
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0) //EOF
			break;

		buf[bytes_read] = '\0';
		//printf("read: %s\n", buf);
		
		//join with leftover, create new str, free old one
		if (leftover)
		{	
			new = ft_strjoin(leftover, buf); //malloc
			free(leftover);
			leftover = NULL;
		}
		else
		  	new = ft_strdup(buf);

		//printf("new str: %s\n", new);
		//free(leftover); //put to null?
		leftover = new;
		
		//scan for nl
		if (is_nl(new))
		 	break;
		else
		{
			free(new);
			new = NULL;
		}
		
		//free(new); //? doesnt work when no nl in file...
		new = NULL;
	}
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover; //constantly created str
	char		*buf;
	char		*newline;

	//safety check
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	if (leftover && ft_strlen(leftover) == 0)//check for nothing else to read
	{
		free(leftover);
		leftover = NULL;
	}
		
	//allocate buf to read into | dynamic = in heap
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);

	//read until nl
	leftover = read_until_nl(fd, buf, leftover);
	//printf("static leftover: %s\n", leftover);
	if (!leftover)
		return (NULL);
	
	//extract newline, update leftover
	newline = get_nl(leftover);
	leftover = update(leftover);

	if (leftover == NULL)
		free (leftover);

	//printf("leftover: %s\n", leftover);
	free (buf);
	return (newline);
}

/*
read and create string until \n (use strjoin, free old leftover)
extract new line, shorten leftover
free buf
return new line


*/

int main (void)
{
	//use open to open file and get fd
	char	*filename = "sample.txt";
	char	*newline;
	
	//read from file
	int	fd = open(filename, O_RDONLY);
	if (fd == -1)//open returns -1 on error
	{
		printf("error opening file\n");
		return (1);
	}
	//print  lines
	for (int i = 0; i < 10; i++)
	{
		newline = get_next_line(fd);
		printf("newline: %s\n", newline);
		free(newline);
		newline = NULL;
	}

	

// 	//read from stdin (terminal)
	
// 	// for (int i = 0; i < 9; i++)
// 	// {
// 	// 	newline = get_next_line(0);
// 	//  	printf("newline: %s\n", newline);
// 	// }
	
	close(fd);
	return (0);
	
}