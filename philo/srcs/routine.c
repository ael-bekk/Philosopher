/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk <ael-bekk@student.13    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:28:03 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/03/01 14:55:32 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosofers.h"

long	get_current_time(long start)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000 - start);
}

void	philo_eating(t_philo *philo)
{
	struct timeval	current_time;
	long			start;

	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(&philo->info->msg);
	printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
		get_current_time(philo->info->start), philo->id, R_FRK);
	pthread_mutex_unlock(&philo->info->msg);
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(&philo->info->msg);
	printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
		get_current_time(philo->info->start), philo->id, L_FRK);
	printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
		get_current_time(philo->info->start), philo->id, EAT);
	pthread_mutex_unlock(&philo->info->msg);
	gettimeofday(&current_time, NULL);
	start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	while (get_current_time(start) < philo->info->time_to_eat)
		usleep(200);
	philo->last_eat = get_current_time(philo->info->start);
	if (philo->info->number_of_times > 0)
		philo->number_of_times++;
}

void	*philo_routin(void *p)
{
	t_philo			*philo;
	struct timeval	current_time;
	long			start;

	philo = (t_philo *)p;
	while (TRUE)
	{
		philo_eating(philo);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_lock(&philo->info->msg);
		printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
			get_current_time(philo->info->start), philo->id, SLP);
		pthread_mutex_unlock(&philo->info->msg);
		gettimeofday(&current_time, NULL);
		start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		while (get_current_time(start) < philo->info->time_to_sleep)
			usleep(100);
		pthread_mutex_lock(&philo->info->msg);
		printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
			get_current_time(philo->info->start), philo->id, THNK);
		pthread_mutex_unlock(&philo->info->msg);
	}
	return (0);
}

void	clear_mutex(pthread_mutex_t *m, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		pthread_mutex_destroy(&m[i]);
}
