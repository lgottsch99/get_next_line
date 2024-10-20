/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:56:18 by lgottsch          #+#    #+#             */
/*   Updated: 2024/10/10 17:00:27 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	y;

	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		new[i] = s1[i];
		i++;
	}
	y = 0;
	while (y < ft_strlen(s2))
	{
		new[i + y] = s2[y];
		y++;
	}
	new[i + y] = '\0';
	return (new);
}

// char	*ft_strdup(const char *s1)
// {
// 	char	*ptr;
// 	int		len;
// 	int		i;

// 	len = ft_strlen(s1) + 1;
// 	ptr = (char *)malloc(sizeof(char) * len);
// 	if (!ptr)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		ptr[i] = (char)s1[i];
// 		i++;
// 	}
// 	return (ptr);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (0);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*tmp;
// 	char			*sub;
// 	unsigned int	i;

// 	if (!s)
// 		return (NULL);
// 	if (start > ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (len > ft_strlen(s) - start)
// 		len = ft_strlen(s) - start;
// 	sub = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!sub)
// 		return (NULL);
// 	tmp = (char *)s;
// 	i = 0;
// 	while (i < len)
// 		sub[i++] = tmp[start++];
// 	sub[i] = '\0';
// 	return (sub);
// }

int	getindexnl(char *leftover)
{
	int	index;

	index = 0;
	while (index < (int)ft_strlen(leftover))
	{
		if (leftover[index] == '\n')
			break ;
		index++;
	}
	return (index);
}
