//Header

#include "gnl.h"

#include <stdio.h>
#include <unistd.h>


char	*update(char *leftover)
{
	int index;
	char	*updated;

	index = getindexnl(leftover);
	updated = ft_substr(leftover, index + 1, ft_strlen(leftover));
	//printf("updated: %s\n", updated);

	return (updated);

	//count how much after nl
	//substr rest

}


char	*get_nl(char *leftover)
{
	int	index;
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

	while (1)
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
			new = ft_strjoin(leftover, buf); //malloc
		else
		  	new = ft_strdup(buf);

		//printf("new str: %s\n", new);
		//free(leftover);
		leftover = new;


		//scan for nl
		if (is_nl(new))
		 	break;

	}
	return (new);

	//}

}

char	*get_next_line(int fd)
{
	static char	*leftover; //constantly created str
	char		*buf;
	char		*newline;

	//safety check
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	//allocate buf to read into
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);

	//read until nl
	leftover = read_until_nl(fd, buf, leftover);
	//printf("static leftover: %s\n", leftover);
	
	//extract newline, update leftover
	newline = get_nl(leftover);
	leftover = update(leftover);


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
	}
	close(fd);
}