/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabusala <rabusala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:51:30 by rabusala          #+#    #+#             */
/*   Updated: 2025/02/27 14:38:12 by rabusala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void	*pointer)
{
	t_philos	*philo;

	philo = (t_philos *)pointer;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (checkdead(philo, philo->info))
			break ;
		print(philo->info, philo->id, "is thinking");
		if (checkdead(philo, philo->info))
			break ;
		if (eating(philo, philo->info) == 1)
			break ;
		if (all_fed(philo->info))
			break ;
		if (checkdead(philo, philo->info))
			break ;
		if (sleaping(philo, philo->info) == 1)
			break ;
	}
	return (pointer);
}

int	create_threads(t_info	*info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		if (pthread_create(&info->philos[i].thread, \
		NULL, &routine, &info->philos[i]) != 0)
			break ;
		i++;
	}
	i = 0;
	while (i < info->num_of_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
