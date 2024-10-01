/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:35:53 by lgottsch          #+#    #+#             */
/*   Updated: 2024/10/01 18:45:03 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Write a function that returns a line read from a
file descriptor
return: Read line: correct behavior
NULL: there is nothing else to read, or an error
occurred

use: read, malloc free
*/

char	*get_next_line(int fd) //passing fd after opening file
{
	char	*newline;
	int		read_bytes; //return value for read
	char	c; //buffer for single char
	size_t	count;

	count = 0;
	//get size of line somehow OR read byte by byte and check until \n
	while ((read_bytes = read(fd, &c, 1)) > 0) //open returns -1 on error
	{
		if (c != "\n")
		//for each byte count++ => size of line to malloc
			count++;
		else
			break;
	}
	//HOW DOES FD KNOW WHERE IN FILE I AM ? DOES IT STOP SOMEWHERE IN FILE??

	
	//malloc buffer to read into
	
	//read into buffer newline using read







	
	return (newline);
}
// need to use some static vars (that keep value until program ends)



#include <stdio.h>
#include <fcntl.h> //for open
int main (void)
{
	//use open to open file and get fd
	char	*filename = "sample.txt";
	char	*newline;
	
	int	fd = open(filename, O_RDONLY);
	if (fd == -1)//open returns -1 on error
	{
		printf("error opening file\n");
		return (1)
	}
	printf("opened file\n");
	
	newline = get_next_line(fd);
	
	
}