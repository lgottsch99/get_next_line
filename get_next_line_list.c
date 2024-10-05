/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:58:11 by lgottsch          #+#    #+#             */
/*   Updated: 2024/10/05 20:36:15 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

void	free_list(t_list *lst)
{
	t_list	*tmp;
	
	if (!lst)
		return;
		
	while(lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp ->next);
	}
		
}


char	*store_leftover(t_list *lst)
{
	char	*leftover;
	int		i;
	int		y;
	char *tmp;
	t_list	*last;
	
	//get to last node in lst and find \n index
	last = ft_lstlast(lst);
	tmp = last->content;
	
	i = 0;
	while (tmp[i] != '\n')
		i++;
	printf("index nl: %i\n", i);
	
	i++; //go over \n in string
	//StORE leftover string
	if (i < BUFFER_SIZE)
	{
		leftover = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		if (!leftover)
			return (NULL);
		
		y = 0;
		while (i < BUFFER_SIZE)
		{
			leftover[y] = tmp[i];
			y++;
			i++;
			
		}
		leftover[y] = '\0';
		printf("leftover: %s\n", leftover);
	}
	else
		leftover = NULL;
	
	return (leftover);
}

char	*extract(t_list *lst) //exract newline from list and create string
{
	char	*str;
	char	*tmp;
	int		lst_size;
	int		i;
	int		y;
	
	//count elements of list? 
	lst_size = ft_lstsize(lst);
	printf("size lst: %i\n", lst_size);
	
	//malloc space for str -HOW LONG?
	str = (char *)malloc(sizeof(char) * ((ft_lstsize(lst) + 1) * BUFFER_SIZE)); //+1 in case \n is at end of buf
	if (!str)
		return (NULL);

	//copy from lst into str including \n, add \0
	i = 0;
	while (lst)//go thru lst
	{
		tmp = lst->content;
		y = 0;
		while (y < BUFFER_SIZE)//copy buffer by buffer, ignore \0 for now, stop at \n
		{
			if (tmp[y - 1] == '\n')
				break ;
			str[i++] = tmp[y++];
		}
		lst = lst->next;	
	}
	str[i] = '\0';
	
	printf("str: %s\n", str);
	return (str);
}

int	scan_nl(char *buf)
{
	int	i;
	
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*create_list(int fd)	//read and create list until nl //store leftover in static
{
	t_list	*lst; //create list until \n found
	t_list	*new_node;
	int		bytes_read;
	char	*buf;
	char	*new_content;
	int	i;



	//malloc buffer to read into
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); //need to \0 ???
	if (!buf)
	 	return (NULL);
	
	while (1)
	{
		//read into buf
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[BUFFER_SIZE] = '\0';
		//  printf("bytes read: %i\n", bytes_read);
		//  printf("buf: %s\n", buf);

		//create new malloc for buffer and copy into
		new_content = (char *)malloc(sizeof(char)* (BUFFER_SIZE + 1));
		if (!new_content)
			return (NULL);
		
		i = 0;
		while (i < (BUFFER_SIZE + 1))
		{
			new_content[i] = buf[i];
			i++;
		}

		//create new node and connect to list
		new_node = ft_lstnew(new_content);
		ft_lstadd_back(&lst, new_node);
		
		//if nl in there or EOF stop loop
		if (scan_nl(buf) || bytes_read == 0)
			break ;
	}

	//test print whole list
	ft_lstiter(lst, print);

	
	free(buf);
	return (lst);
}

char	*get_next_line(int fd)
{
	static char	*leftover; //storing
	static int	indicator;
	char			*newline;
	t_list	*lst;
	t_list	*new_node;

	printf("leftover is: %s\n", leftover);
	printf("indicator %i\n", indicator);
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
		
	//how to check if there is some leftover & how to join with list?
	if (indicator > 0)
	{
		printf("we have leftover\n");
		new_node = ft_lstnew(leftover);
		ft_lstadd_back(&lst, new_node);
	}

	indicator++;

	lst = create_list(fd);
	newline = extract(lst);
	leftover = store_leftover(lst);
	
	//free whole list
	free_list(lst);
	
	return (newline);
}

/* STRATEGY

	if static not empty, get it as first node in list
	read and create list nodes and connect until \n found
	extract new line, store leftover in static (also list node)
	free whole list
	return new line
	
	
*/

int main (void)
{
	
}
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
	for (int i = 0; i < 2; i++)
	{
		newline = get_next_line(fd);
		printf("newline: %s\n", newline);
	}
	close(fd);

	
}