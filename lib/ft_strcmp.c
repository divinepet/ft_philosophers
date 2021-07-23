#include "../lib.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char*)str1;
	s2 = (unsigned char*)str2;
	while (*s1 != '\0' || *s2 != '\0')
		if (*s1++ != *s2++)
			return (*--s1 - *--s2);
	return (0);
}