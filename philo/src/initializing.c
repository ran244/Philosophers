/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneem <raneem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:03:26 by rabusala          #+#    #+#             */
/*   Updated: 2025/02/19 21:14:31 by raneem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_locks(t_info *info)
{
	if (pthread_mutex_init(&info->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->d_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->full_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->meal_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_info(t_info	*info, char	**v)
{
	int	i;

	if (init_locks(info))
		return (1);
	info->num_of_philos = ft_atoi(v[1]);
	info->time_to_die = ft_atoi(v[2]);
	info->time_to_eat = ft_atoi(v[3]);
	info->time_to_sleap = ft_atoi(v[4]);
	info->birthdate = get_time();
	info->deadforever = 0;
	info->full = 0;
	i = 0;
	while (i < info->num_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (v[5])
		info->num_of_meals = ft_atoi(v[5]);
	else
		info->num_of_meals = -1;
	return (0);
}

void	initphilo(t_info	*info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].eaten_meals = 0;
		info->philos[i].last_meal = get_time();
		info->philos[i].lfork = &info->forks[i];
		if (i == 0)
			info->philos[i].rfork = &info->forks[info->num_of_philos - 1];
		else
			info->philos[i].rfork = &info->forks[i - 1];
		info->philos[i].info = info;
		i++;
	}
}
