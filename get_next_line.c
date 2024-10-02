/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:35:53 by lgottsch          #+#    #+#             */
/*   Updated: 2024/10/02 21:08:36 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <fcntl.h> //for open
#include <unistd.h> //for read
#include <stdlib.h> //for malloc
#include <stdio.h>



/*
Write a function that returns a line read from a
file descriptor
return: Read line: correct behavior
NULL: there is nothing else to read, or an error
occurred

use: read, malloc free
*/

//need some macro BUFFER_SiZE (value set at compilation)
char	*get_next_line(int fd)
{
	int		i;
	//static	char	*safe; //to store leftover string in
	char	temp[BUFFER_SIZE]; //buffer to read into, as big as buffer size
	char	*check;
	char	*newline;

	//read buffer size and store in temp-array
	read(fd, &temp, BUFFER_SIZE);
	printf("buffer: %s\n", temp);
	
	i = 0;
	//check for \n in temp
	if ((check = ft_strchr(temp, '\n'))!= NULL) //CASE 1 read more than whole line, \n is there
	{
		while (temp[i] != '\n')
			i++;
		i = i + 1; //for \n char
		printf("len newline: %i\n", i);
	}

	newline = ft_substr(temp, 0, i);	
		//if yes, return string until \n 
		//and store leftover in safe
		
		
		//if not store and do again







		
	
	return (newline);
}
// need to use some static vars (that keep value until program ends)


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
	printf("opened file\n");
	
	newline = get_next_line(fd);
	printf("newline: %s\n", newline);
	// newline = get_next_line(fd);
	// printf("newline: %s\n", newline);

}