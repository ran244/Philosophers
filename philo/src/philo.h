/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneem <raneem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:14:44 by rabusala          #+#    #+#             */
/*   Updated: 2025/02/19 21:13:56 by raneem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

# define PHILO_MAX 202

typedef struct s_philos
{
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_t		thread;
	struct s_info	*info;
	size_t			last_meal;
	int				id;
	int				eaten_meals;
}	t_philos;

typedef struct s_info
{
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	full_lock;
	pthread_mutex_t	d_lock;
	pthread_mutex_t	forks[PHILO_MAX];
	t_philos		philos[PHILO_MAX];
	size_t			time_to_die;
	size_t			birthdate;
	int				num_of_philos;
	int				time_to_eat;
	int				time_to_sleap;
	int				num_of_meals;
	int				deadforever;
	int				full;
}	t_info;
size_t	get_time(void);
void	print(t_info *info, int id, char *message);
void	initphilo(t_info *info);
void	*routine(void *pointer);
void	thinking(t_philos *philo);
void	ft_free(t_info *info);
int		init_info(t_info *info, char **v);
int		checkdegit(char *str);
int		ft_atoi(const char *nptr);
int		checkargs(char **v);
int		ft_strlen(char *str);
int		ft_usleep(t_info *info, size_t ms);
int		checkdead(t_philos *philo, t_info *info);
int		all_fed(t_info *info);
int		sleaping(t_philos *philo, t_info *info);
int		eating(t_philos *philo, struct s_info *info);
int		eating2(t_philos *philo, struct s_info *info);
int		deadforever(t_info *info);
int		create_threads(t_info *info);
int		init_locks(t_info *info);
#endif
