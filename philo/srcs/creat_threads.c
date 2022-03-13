/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk <ael-bekk@student.13    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:32:00 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/02/28 16:10:55 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosofers.h"

void	creat_threads(t_philo *philos, t_glob *info)
{
	int				i;
	struct timeval	current_time;

	i = -1;
	while (++i < info->nb_philos)
		pthread_mutex_init(&info->forks[i], NULL);
	pthread_mutex_init(&info->msg, NULL);
	i = -1;
	while (++i < info->nb_philos)
	{
		gettimeofday(&current_time, NULL);
		info->start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		philos[i].id = i + 1;
		philos[i].right = &info->forks[i];
		philos[i].left = &info->forks[(i + 1) % info->nb_philos];
		philos[i].info = info;
		philos[i].last_eat = get_current_time(info->start);
		philos[i].number_of_times = 0;
	}
	i = -1;
	while (++i < info->nb_philos)
	{
		pthread_create(&philos[i].philo, NULL, &philo_routin, &philos[i]);
		usleep(100);
	}
}
