/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneem <raneem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:11:47 by rabusala          #+#    #+#             */
/*   Updated: 2025/02/19 21:17:01 by raneem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int c, char **v)
{
	t_info	info;

	if (c == 6 || c == 5)
	{
		if (checkargs(v) == 0)
			return (0);
		if (init_info(&info, v))
		{
			printf("ERROR: in creating the locks\n");
			return (0);
		}
		initphilo(&info);
		if (create_threads(&info) == 1)
		{
			printf("ERROR: in creating threads\n");
			return (1);
		}
		ft_free(&info);
	}
	else
		printf("ERROR: invalid number of arguments\n");
	return (0);
}
