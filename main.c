#include "lib.h"

void	start_simulation(t_metadata *metadata, t_data *all, t_table *table)
{
	int		i;
	int		status;

	i = 0;
	while (i != all->ph_number)
	{
		metadata[i].id = i;
		(&metadata[i])->all = all;
		(&metadata[i])->table = table;
		(&metadata[i])->t_last_eat = time_now();
		metadata[i].status = pthread_create(&metadata[i].thread,
				NULL, life_cycle_thread, &metadata[i]);
		if (metadata[i].status != 0)
			return ;
		i++;
	}
	i = 0;
	while (i != all->ph_number)
	{
		metadata[i].status = pthread_join(metadata[i].thread,
				(void **)&metadata[i].status_join);
		if (metadata[i].status != 0)
			return ;
		i++;
	}
}

int	create_philosophers(t_data *all)
{
	int			i;
	t_metadata	*metadata;
	t_table		table;

	i = 0;
	all->t_start = time_now();
	all->philo_dead = 0;
	table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* all->ph_number);
	metadata = (t_metadata *)malloc(sizeof(t_metadata) * all->ph_number);
	if (!table.forks || !metadata)
		return (1);
	pthread_mutex_init(&table.text, NULL);
	pthread_mutex_init(&table.time, NULL);
	pthread_mutex_init(&table.death, NULL);
	while (i != all->ph_number)
		pthread_mutex_init(&table.forks[i++], NULL);
	start_simulation(metadata, all, &table);
	return (0);
}

int	arguments_check(char **av, int i)
{
	int	j;

	j = 0;
	if (!av[i])
		return (0);
	while (av[i][j] != '\0')
	{
		if (!ft_isdigit(av[i][j]))
			return (1);
		j++;
	}
	return (arguments_check(av, i + 1));
}

int	main(int ac, char **av)
{
	t_data	all;

	if (ac < 5 || ac > 6)
		return (1);
	if (arguments_check(av, 1))
		return (1);
	all.must_eat = -1;
	all.ph_number = ft_atoi(av[1]);
	all.t_die = ft_atoi(av[2]);
	all.t_eat = ft_atoi(av[3]);
	all.t_sleep = ft_atoi(av[4]);
	if (av[5])
		all.must_eat = ft_atoi(av[5]);
	if (all.ph_number < 2 || !all.t_die || !all.t_eat || !all.t_sleep)
		return (1);
	return (create_philosophers(&all));
}
