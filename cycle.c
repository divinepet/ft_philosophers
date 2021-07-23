#include "lib.h"

void	ft_philo_eat_even(t_metadata *philosopher)
{
	pthread_mutex_lock(&philosopher->table->forks[philosopher->right_fork]);
	print("has taken a fork\n", philosopher);
	pthread_mutex_lock(&philosopher->table->forks[philosopher->left_fork]);
	print("has taken a fork\n", philosopher);
	pthread_mutex_lock(&philosopher->table->time);
	philosopher->last_eat_time = time_now();
	pthread_mutex_unlock(&philosopher->table->time);
	print("is eating\n", philosopher);
	_sleep(philosopher->all->time_to_eat);
	pthread_mutex_unlock(&philosopher->table->forks[philosopher->right_fork]);
	pthread_mutex_unlock(&philosopher->table->forks[philosopher->left_fork]);
	print("is sleeping\n", philosopher);
	_sleep(philosopher->all->time_to_sleep);
	print("is thinking\n", philosopher);
}

void	ft_philo_eat_neven(t_metadata *philosopher)
{
	pthread_mutex_lock(&philosopher->table->forks[philosopher->left_fork]);
	print("has taken a fork\n", philosopher);
	pthread_mutex_lock(&philosopher->table->forks[philosopher->right_fork]);
	print("has taken a fork\n", philosopher);
	pthread_mutex_lock(&philosopher->table->time);
	philosopher->last_eat_time = time_now();
	pthread_mutex_unlock(&philosopher->table->time);
	print("is eating\n", philosopher);
	_sleep(philosopher->all->time_to_eat);
	pthread_mutex_unlock(&philosopher->table->forks[philosopher->left_fork]);
	pthread_mutex_unlock(&philosopher->table->forks[philosopher->right_fork]);
	print("is sleeping\n", philosopher);
	_sleep(philosopher->all->time_to_sleep);
	print("is thinking\n", philosopher);
}

void	*ft_philo_dead(void *metadata)
{
	t_metadata		*philosopher_dead;

	philosopher_dead = metadata;
	while (1)
	{
		pthread_mutex_lock(&philosopher_dead->table->time);
		if ((time_now() - philosopher_dead->last_eat_time)
			> philosopher_dead->all->time_to_die)
			break ;
		pthread_mutex_unlock(&philosopher_dead->table->time);
	}
	pthread_mutex_unlock(&philosopher_dead->table->time);
	if (philosopher_dead->count_eat !=
		philosopher_dead->all->must_eat)
		print("died\n", philosopher_dead);
	philosopher_dead->all->philo_dead = 1;
	pthread_mutex_unlock(&philosopher_dead->table->death);
	return (NULL);
}

void*		life_cycle(void *metadata)
{
	pthread_t	thread_dead;
	int			status;
	int			status_join;
	t_metadata		*philosopher;

	philosopher = metadata;
	philosopher->left_fork = philosopher->id;
	philosopher->right_fork = philosopher->id - 1;
	if (philosopher->right_fork < 0)
		philosopher->right_fork = philosopher->all->ph_number - 1;
	status = philosopher->id % 2;
	pthread_create(&thread_dead, NULL, ft_philo_dead, philosopher);
	philosopher->count_eat = 0;
	while (philosopher->count_eat != philosopher->all->must_eat && philosopher->all->philo_dead != 1)
	{
		if (status == 1)
			ft_philo_eat_neven(philosopher);
		if (status != 1)
			ft_philo_eat_even(philosopher);
		philosopher->count_eat++;
	}
	status = pthread_join(thread_dead, (void**)&status_join);
	return (NULL);
}
