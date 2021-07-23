#include "lib.h"

int		start_simulation(t_metadata *metadata, t_data *all, t_table *table)
{
	int		i;

	i = 0;
	while (i != all->number_of_philosophers)
	{
		metadata[i].philo_id = i;
		(&metadata[i])->all = all;
		(&metadata[i])->table = table;
		(&metadata[i])->last_eat_time = time_now();
		metadata[i].status = pthread_create(&metadata[i].thread, NULL, life_cycle, &metadata[i]);
		if (metadata[i].status != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i != all->number_of_philosophers)
	{
		metadata[i].status = pthread_join(metadata[i].thread, (void**)&metadata[i].status_join);
		if (metadata[i].status != 0)
			return (1);
		i++;
	}
	return (0);
}

int				create_philosophers(t_data *all)
{
	int		i;
	t_metadata	*metadata;
	t_table	table;

	i = 0;
	all->start_time = time_now();
	all->philo_dead = 0;
	table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * all->number_of_philosophers);
	metadata = (t_metadata *)malloc(sizeof(t_metadata) * all->number_of_philosophers);
	if (!table.forks || !metadata)
		return (1);
	pthread_mutex_init(&table.text, NULL);
	pthread_mutex_init(&table.time, NULL);
	pthread_mutex_init(&table.death, NULL);
	while (i != all->number_of_philosophers)
		pthread_mutex_init(&table.forks[i++], NULL);
	start_simulation(metadata, all, &table);
	return (0);
}

int		arguments_check(char **av, int i)
{
	int j;

	j = 0;
	while (av[i][j] != '\0') {
		if (!ft_isdigit(av[i][j]))
			return (1);
		j++;
	}
	if (av[i + 1][j] != '\0')
		arguments_check(av, i + 1);
	return (0);
}

int				main(int ac, char **av)
{
	t_data all;

	if (ac < 5 || ac > 6)
		return (1);
	if (arguments_check(av, 1))
		return (1);
	all.number_of_times_each_philosopher_must_eat = -1;
	all.number_of_philosophers = ft_atoi(av[1]);
	all.time_to_die = ft_atoi(av[2]);
	all.time_to_eat = ft_atoi(av[3]);
	all.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		all.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	if (all.number_of_philosophers < 2 || all.time_to_die == 0 || all.time_to_eat == 0 || all.time_to_sleep == 0)
		return (1);
	return create_philosophers(&all);
	return (0);
}
