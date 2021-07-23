#include "lib.h"

void	_sleep(long time)
{
	long	fix_time;

	fix_time = time_now();
	while (time_now() - fix_time < time)
		usleep(1);
}

void	ft_write_text(char *s, t_metadata *filo, int flag)
{
	pthread_mutex_lock(&filo->table->text);
	pthread_mutex_lock(&filo->table->time);
	pthread_mutex_unlock(&filo->table->time);
	pthread_mutex_lock(&filo->table->death);
	if (filo->all->philo_dead != 1)
		printf("%s[%ldms]%s philosopher %d%s%s", BLUE, time_now() - filo->all->start_time, CYAN, filo->philo_id + 1, s, RESET);	
	if (!flag)
		pthread_mutex_unlock(&filo->table->death);
	pthread_mutex_unlock(&filo->table->text);
}

long	time_now(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
