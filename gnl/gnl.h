//HEADER


#include <stdlib.h> //malloc, free
#include <string.h> //size t
#include <fcntl.h> //read open close

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	getindexnl(char *leftover);





