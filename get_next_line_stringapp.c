/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_stringapp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:35:53 by lgottsch          #+#    #+#             */
/*   Updated: 2024/10/05 20:28:25 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

/* TO DO
make it work for: 
	buffer 10000000
	buffer -5
	
	what if txt file empty?
	fix memory leaks
	
*/

//test: if fd exists?, check: smallest bufsize is 1, check if bufsize <=0
//check stack overflow buffer
//what if txt file empty?


char	*read_buffer_until_nl(int fd, char *leftover)
{
	int		nl;
	int		bytes_read;
	char 	*safe;
	char	*temp; //buffer to read into, as big as buffer size + 1 for \0
	char	*check; //ptr to \n

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);

	bytes_read = 0;
	nl = 0;
	while (nl == 0)
	{
		bytes_read = read(fd, &temp, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		else
			temp[BUFFER_SIZE] = '\0'; //need to terminate for str handling ft

		check = ft_strchr(temp, '\n');//returns NULL if char NOT found
		if (check != NULL)
			nl = 1;
		
		//create safe
		if (leftover)
			safe = ft_strjoin(leftover, temp);
		else
			safe = ft_strdup(temp);
		//copy content in leftover
		leftover = safe;
		ft_bzero(temp, ft_strlen(temp));
	//	printf("leftover: %s\n", leftover);
	}
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover; //to keep and store leftovers
	char *safe;
	static int	call;
	char	*newline;
	char	*check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	call++;
	if (call == 1)
	{
		//printf("1st call\n");
		
		leftover = read_buffer_until_nl(fd, leftover);
		
		//extract new line, update leftover, return new line
		newline = ft_substr(leftover, 0, ft_strchr(leftover, '\n') - leftover + 1); //+1 to include 
		safe = ft_substr(leftover, ft_strchr(leftover, '\n') - leftover + 1, ft_strlen(leftover) - (ft_strchr(leftover, '\n') - leftover + 1));
		leftover = safe;
	//	printf("new leftover: %s\n", leftover);
		return (newline);
	}
	if (call > 1)
	{
		//printf("2nd or moree call\n");
		// check if leftover content exist
		if (leftover[0] && ((check = ft_strchr(leftover, '\n')) != NULL))
		{
			// 	return newline and store leftover in static
			newline = ft_substr(leftover, 0, ft_strchr(leftover, '\n') - leftover + 1); //+1 to include 
			safe = ft_substr(leftover, ft_strchr(leftover, '\n') - leftover + 1, ft_strlen(leftover) - (ft_strchr(leftover, '\n') - leftover + 1));
			leftover = safe;
			//printf("new leftover: %s\n", leftover);
			return (newline);
		}
		else
		{
			leftover = read_buffer_until_nl(fd, leftover);

			//extract new line, update leftover, return new line
			newline = ft_substr(leftover, 0, ft_strchr(leftover, '\n') - leftover + 1); //+1 to include 
			safe = ft_substr(leftover, ft_strchr(leftover, '\n') - leftover + 1, ft_strlen(leftover) - (ft_strchr(leftover, '\n') - leftover + 1));
			leftover = safe;
			//printf("new leftover: %s\n", leftover);
			return (newline);
		}
	}
	else
	{
		// if no:
		// 	read buffer until \n in there
		// 	return newline, store leftover in static

		leftover = read_buffer_until_nl(fd, leftover);

		//extract new line, update leftover, return new line
		newline = ft_substr(leftover, 0, ft_strchr(leftover, '\n') - leftover + 1); //+1 to include 
		safe = ft_substr(leftover, ft_strchr(leftover, '\n') - leftover + 1, ft_strlen(leftover) - (ft_strchr(leftover, '\n') - leftover + 1));
		leftover = safe;
		//printf("new leftover: %s\n", leftover);
		return (newline);			
	}
}


/*	STRATEGY

if 1. call to ft:
	read buffer until \n in there
	(if no \n in buffer, store buffer in static and do again until \n there)
	
	return newline, store leftover in static

2. or more call to ft:
	check if leftover content exist
		if yes: 
			check if \n in leftover
			if yes:
				return newline and store leftover in static
			if no:
				read buffer until \n in there
				join leftover with read content
				return newline and store leftover

		if no: (same as first call)
			read buffer until \n in there
			return newline, store leftover in static


->IF READ RETURNS 0 anywhere:
	join whatever is in buffer + safe and return (last line)


WHEN TO STOP? End of file reached -> read returns 0
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