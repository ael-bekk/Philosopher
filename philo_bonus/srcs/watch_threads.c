/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk <ael-bekk@student.13    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:49:53 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/03/02 14:08:39 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosofers.h"

void	watch_thread(t_philo *philo)
{
	while (TRUE)
	{
		sem_wait(philo->info->msg);
		if (get_current_time(philo->last_eat + philo->info->start)
			>= philo->info->time_to_die)
		{
			printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
				get_current_time(philo->info->start), philo->id, DIED);
			exit(1);
		}
		sem_post(philo->info->msg);
		if (philo->info->number_of_times > 0
			&& philo->number_of_times >= philo->info->number_of_times)
			exit(2);
	}
}

int	watch_prosses(t_philo *philo)
{
	int				i;
	int				status;

	while (TRUE)
	{
		if (waitpid(-1, &status, 0))
		{
			if (status == 256)
			{
				i = -1;
				while (++i < philo->info->nb_philos)
					kill(philo[i].pid, 15);
				exit(0);
			}
			i = 0;
			while (++i < philo->info->nb_philos)
				waitpid(-1, NULL, 0);
			printf("⏳%s%ld ms%s\n", CYN,
				get_current_time(philo->info->start), FINISH);
			exit(0);
		}
	}
}
