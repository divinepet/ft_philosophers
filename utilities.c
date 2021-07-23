#include "lib.h"

void	print(char *str, t_metadata *philosopher)
{
	pthread_mutex_lock(&philosopher->table->text);
	pthread_mutex_lock(&philosopher->table->death);
	if (philosopher->all->philo_dead != 1)
		printf("%s[%ldms]%s philosopher %d %s%s", BLUE, time_now() - philosopher->all->start_time, CYAN, philosopher->id + 1, str, RESET);	
	if (ft_strcmp(str, "died"))
		pthread_mutex_unlock(&philosopher->table->death);
	pthread_mutex_unlock(&philosopher->table->text);
}

void	_sleep(long time)
{
	long	tmp;

	tmp = time_now();
	while (time_now() - tmp < time)
		usleep(1);
}

long	time_now(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
