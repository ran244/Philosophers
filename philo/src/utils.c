/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneem <raneem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:00:38 by rabusala          #+#    #+#             */
/*   Updated: 2025/02/19 21:09:40 by raneem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(t_info *info, size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (checkdead(info->philos, info) == 1)
			return (1);
		usleep(500);
	}
	return (0);
}

int	checkdead(t_philos	*philo, t_info	*info)
{
	size_t	n;

	n = philo->info->time_to_die;
	pthread_mutex_lock(&info->dead_lock);
	if (info->deadforever)
	{
		pthread_mutex_unlock(&info->dead_lock);
		return (1);
	}
	if (get_time() - philo->last_meal >= n)
	{
		print(info, philo->id, "died");
		info->deadforever = 1;
		pthread_mutex_unlock(&info->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&info->dead_lock);
	return (0);
}

int	all_fed(t_info	*info)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (info->num_of_meals == -1)
		return (0);
	while (i < info->num_of_philos)
	{
		if (info->philos[i].eaten_meals >= info->num_of_meals)
		{
			pthread_mutex_lock(&info->full_lock);
			full++;
			pthread_mutex_unlock(&info->full_lock);
		}
		i++;
	}
	if (full == info->num_of_philos)
		return (1);
	return (0);
}

void	ft_free(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->dead_lock);
	pthread_mutex_destroy(&info->d_lock);
	pthread_mutex_destroy(&info->meal_lock);
	pthread_mutex_destroy(&info->full_lock);
}
