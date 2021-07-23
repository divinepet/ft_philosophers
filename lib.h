#ifndef LIB_H
# define LIB_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
#define RESET  "\x1B[0m"
#define YELLOW  "\x1B[0;33m"
#define BLUE  "\x1B[1;34m"
#define CYAN  "\x1B[0;36m"

typedef struct		s_data
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				number_of_times_each_philosopher_must_eat;
	int				philo_dead;
}					t_data;

typedef struct		s_table
{
	pthread_mutex_t *forks;
	pthread_mutex_t time;
	pthread_mutex_t text;
	pthread_mutex_t death;
}					t_table;

typedef struct		s_metadata
{
	pthread_t		thread;
	int				philo_id;
	int				status;
	int				status_join;
	int				left_fork;
	int				right_fork;
	long			last_eat_time;
	int				count_eat;
	t_data			*all;
	t_table			*table;
}					t_metadata;

// int					create_philosophers(t_data *all);
void*				life_cycle(void *ptr);

void				_sleep(long time);
void				ft_write_text(char *s, t_metadata *filo, int flag);
long				time_now(void);

int					ft_atoi(const char *str);
char*				ft_itoa(int n);
char*				ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(char *str);
int					ft_isdigit(int ch);

#endif