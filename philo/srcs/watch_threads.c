/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk <ael-bekk@student.13    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:49:53 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/02/28 16:18:08 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosofers.h"

int	exit_threads(int ex, t_philo *philo)
{
	if (ex == 1)
		printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
			get_current_time(philo->info->start), philo->id, DIED);
	else
		printf("⏳%s%ld ms%s\n", CYN,
			get_current_time(philo->info->start), FINISH);
	return (1);
}

int	watch_threads(t_philo *philo)
{
	int				i;
	int				valid;

	while (TRUE)
	{
		i = -1;
		valid = FALSE;
		while (++i < philo->info->nb_philos)
		{
			pthread_mutex_lock(&philo->info->msg);
			if (get_current_time(philo[i].last_eat + philo->info->start)
				>= philo->info->time_to_die)
				return (exit_threads(1, &philo[i]));
			pthread_mutex_unlock(&philo->info->msg);
			if (philo->info->number_of_times < 0
				|| philo[i].number_of_times < philo->info->number_of_times)
				valid = TRUE;
		}
		pthread_mutex_lock(&philo->info->msg);
		if (!valid)
			return (exit_threads(2, philo));
		pthread_mutex_unlock(&philo->info->msg);
	}
}
