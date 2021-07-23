#include "../lib.h"

static	int		n_length(int n)
{
	int	mem;

	mem = 1;
	if (n < 0)
	{
		mem++;
		n *= -1;
	}
	while (n >= 10)
	{
		n = n / 10;
		mem++;
	}
	return (mem);
}

static	char	*final(int n, int mem, char *str, int q)
{
	int	ink;

	ink = (n >= 0) ? 1 : -1;
	n = (n < 0) ? (n *= -1) : n;
	str[mem] = '\0';
	while (mem-- && n >= 10)
	{
		str[mem] = (n % 10) + '0';
		n /= 10;
	}
	str[mem] = n + '0';
	if (ink < 0)
		str[--mem] = '-';
	if (q)
		str[10] = '8';
	return (str);
}

char			*ft_itoa(int n)
{
	int		i;
	int		mem;
	int		q;
	char	*str;

	q = 0;
	i = 0;
	if (n == -2147483648)
	{
		n++;
		q = 1;
	}
	mem = n_length(n);
	if (!(str = (char*)malloc(sizeof(char) * (mem + 1))))
		return (NULL);
	return (final(n, mem, str, q));
}