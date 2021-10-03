#include "lib.h"

void	eating(t_metadata *philosopher, int status)
{
	if (status == 1)
	{
		pthread_mutex_lock(&philosopher->table->forks[philosopher->left_fork]);
		print("has taken a fork\n", philosopher);
		pthread_mutex_lock(&philosopher->table->forks[philosopher->right_fork]);
		print("has taken a fork\n", philosopher);
	}
	else
	{
		pthread_mutex_lock(&philosopher->table->forks[philosopher->right_fork]);
		print("has taken a fork\n", philosopher);
		pthread_mutex_lock(&philosopher->table->forks[philosopher->left_fork]);
		print("has taken a fork\n", philosopher);
	}
	pthread_mutex_lock(&philosopher->table->time);
	philosopher->t_last_eat = time_now();
	print("is eating\n", philosopher);
	philosopher->count_eat++;
	pthread_mutex_unlock(&philosopher->table->time);
	_sleep(philosopher->all->t_eat);
	pthread_mutex_unlock(&philosopher->table->forks[philosopher->left_fork]);
	pthread_mutex_unlock(&philosopher->table->forks[philosopher->right_fork]);
	print("is sleeping\n", philosopher);
	_sleep(philosopher->all->t_sleep);
	print("is thinking\n", philosopher);
}

void	*dead_philosopher_thread(void *metadata)
{
	t_metadata		*ph;

	ph = metadata;
	while (1)
	{
		pthread_mutex_lock(&ph->table->time);
		if ((time_now() - ph->t_last_eat) > ph->all->t_die)
			break ;
		pthread_mutex_unlock(&ph->table->time);
	}
	pthread_mutex_unlock(&ph->table->time);
	if (ph->count_eat != ph->all->must_eat)
	{
		print("died\n", ph);
		ph->all->philo_dead = 1;
	}
	pthread_mutex_unlock(&ph->table->death);
	return (NULL);
}

void	*life_cycle_thread(void *metadata)
{
	pthread_t	thread_dead;
	int			thread_number;
	int			status;
	t_metadata	*ph;

	ph = metadata;
	ph->left_fork = ph->id;
	ph->right_fork = ph->id - 1;
	if (ph->right_fork < 0)
		ph->right_fork = ph->all->ph_number - 1;
	thread_number = ph->id % 2;
	pthread_create(&thread_dead, NULL, dead_philosopher_thread, ph);
	ph->count_eat = 0;
	while (ph->all->philo_dead != 1 && ph->count_eat != ph->all->must_eat)
	{
		eating(ph, thread_number);
	}
	pthread_join(thread_dead, (void **)&status);
	return (NULL);
}
