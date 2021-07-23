#include "lib.h"

void	ft_philo_eat_even(t_metadata *filo)
{
	pthread_mutex_lock(&filo->table->forks[filo->right_fork]);
	print("has taken a fork\n", filo);
	pthread_mutex_lock(&filo->table->forks[filo->left_fork]);
	print("has taken a fork\n", filo);
	pthread_mutex_lock(&filo->table->time);
	filo->last_eat_time = time_now();
	pthread_mutex_unlock(&filo->table->time);
	print("is eating\n", filo);
	_sleep(filo->all->time_to_eat);
	pthread_mutex_unlock(&filo->table->forks[filo->right_fork]);
	pthread_mutex_unlock(&filo->table->forks[filo->left_fork]);
	print("is sleeping\n", filo);
	_sleep(filo->all->time_to_sleep);
	print("is thinking\n", filo);
}

void	ft_philo_eat_neven(t_metadata *filo)
{
	pthread_mutex_lock(&filo->table->forks[filo->left_fork]);
	print("has taken a fork\n", filo);
	pthread_mutex_lock(&filo->table->forks[filo->right_fork]);
	print("has taken a fork\n", filo);
	pthread_mutex_lock(&filo->table->time);
	filo->last_eat_time = time_now();
	pthread_mutex_unlock(&filo->table->time);
	print("is eating\n", filo);
	_sleep(filo->all->time_to_eat);
	pthread_mutex_unlock(&filo->table->forks[filo->left_fork]);
	pthread_mutex_unlock(&filo->table->forks[filo->right_fork]);
	print("is sleeping\n", filo);
	_sleep(filo->all->time_to_sleep);
	print("is thinking\n", filo);
}

void	*ft_philo_dead(void *metadata)
{
	t_metadata		*filo_dead;

	filo_dead = metadata;
	while (1)
	{
		pthread_mutex_lock(&filo_dead->table->time);
		if ((time_now() - filo_dead->last_eat_time)
			> filo_dead->all->time_to_die)
			break ;
		pthread_mutex_unlock(&filo_dead->table->time);
	}
	pthread_mutex_unlock(&filo_dead->table->time);
	if (filo_dead->count_eat !=
		filo_dead->all->number_of_times_each_philosopher_must_eat)
		print("died\n", filo_dead);
	filo_dead->all->philo_dead = 1;
	pthread_mutex_unlock(&filo_dead->table->death);
	return (NULL);
}

void	ft_init_filo(t_metadata *filo)
{
	filo->left_fork = filo->philo_id;
	filo->right_fork = filo->philo_id - 1;
	if (filo->right_fork < 0)
		filo->right_fork = filo->all->number_of_philosophers - 1;
}

void*		life_cycle(void *metadata)
{
	pthread_t	thread_dead;
	int			status;
	int			status_join;
	t_metadata		*filo;

	filo = metadata;
	ft_init_filo(filo);
	status = filo->philo_id % 2;
	pthread_create(&thread_dead, NULL, ft_philo_dead, filo);
	filo->count_eat = 0;
	while (filo->count_eat != filo->all->number_of_times_each_philosopher_must_eat && filo->all->philo_dead != 1)
	{
		if (status == 1)
			ft_philo_eat_neven(filo);
		if (status != 1)
			ft_philo_eat_even(filo);
		filo->count_eat++;
	}
	status = pthread_join(thread_dead, (void**)&status_join);
	return (NULL);
}
