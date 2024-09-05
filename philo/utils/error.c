#include "../philo.h"

int	error(char *message)
{
	printf(RED"error - ");
	printf(RST"%s\n", message);
	return (0);
}