/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabusala <rabusala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:05:41 by rabusala          #+#    #+#             */
/*   Updated: 2025/02/23 11:53:29 by rabusala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_info	*info, int id, char	*message)
{
	pthread_mutex_lock(&info->write_lock);
	if (!info->deadforever)
	{
		printf("%ld", (get_time() - info->birthdate));
		printf(" %d %s\n", id, message);
	}
	pthread_mutex_unlock(&info->write_lock);
}

int	sleaping(t_philos *philo, t_info *info)
{
	print(info, philo->id, "is sleeping");
	if (ft_usleep(info, info->time_to_sleap) == 1)
		return (1);
	return (0);
}

int	eating(t_philos *philo, struct s_info *info)
{
	pthread_mutex_lock(philo->lfork);
	if (checkdead(philo, info))
	{
		pthread_mutex_unlock(philo->lfork);
		return (1);
	}
	print(info, philo->id, "has taken a fork");
	if (info->num_of_philos == 1)
		ft_usleep(info, info->time_to_die);
	if (checkdead(philo, info))
	{
		pthread_mutex_unlock(philo->lfork);
		return (1);
	}
	pthread_mutex_lock(philo->rfork);
	if (checkdead(philo, info))
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
		return (1);
	}
	print(info, philo->id, "has taken a fork");
	return (eating2(philo, info));
}

int	eating2(t_philos *philo, struct s_info *info)
{
	print(info, philo->id, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->info->meal_lock);
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->info->meal_lock);
	if (ft_usleep(philo->info, info->time_to_eat) == 1)
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
		return (1);
	}
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	return (0);
}
