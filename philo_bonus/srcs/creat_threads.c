/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk <ael-bekk@student.13    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:32:00 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/03/02 14:30:06 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosofers.h"

void	init_prosses1(t_glob *info)
{
	char	*sem;
	int		i;

	i = -1;
	while (++i < info->nb_philos)
	{
		sem = ft_itoa(i);
		sem_unlink(sem);
		info->forks[i] = sem_open(sem, O_CREAT, 0644, 1);
		free(sem);
	}
	sem_unlink("print");
	info->msg = sem_open("print", O_CREAT, 0644, 1);
}

void	init_prosses2(t_philo *philos, t_glob *info)
{
	int				i;
	struct timeval	current_time;

	i = -1;
	while (++i < info->nb_philos)
	{
		gettimeofday(&current_time, NULL);
		info->start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		philos[i].id = i + 1;
		philos[i].right = info->forks[i];
		philos[i].left = info->forks[(i + 1) % info->nb_philos];
		philos[i].info = info;
		philos[i].last_eat = get_current_time(info->start);
		philos[i].number_of_times = 0;
	}
}

void	creat_prosses(t_philo *philos, t_glob *info)
{
	int	i;

	init_prosses1(info);
	init_prosses2(philos, info);
	i = -1;
	while (++i < info->nb_philos)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			pthread_create(&philos[i].philo, NULL, &philo_routin, &philos[i]);
			watch_thread(&philos[i]);
		}
		usleep(100);
	}
}
