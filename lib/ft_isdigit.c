#include "../lib.h"

int	ft_isdigit(int ch)
{
	return ((ch >= '0' && ch <= '9') ? 1 : 0);
}