/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk <ael-bekk@student.13    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:28:03 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/03/01 18:53:26 by ael-bekk         ###   ########.fr       */
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

	sem_wait(philo->right);
	sem_wait(philo->info->msg);
	printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
		get_current_time(philo->info->start), philo->id, R_FRK);
	sem_post(philo->info->msg);
	sem_wait(philo->left);
	sem_wait(philo->info->msg);
	printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
		get_current_time(philo->info->start), philo->id, L_FRK);
	printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
		get_current_time(philo->info->start), philo->id, EAT);
	sem_post(philo->info->msg);
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
		sem_post(philo->left);
		sem_post(philo->right);
		sem_wait(philo->info->msg);
		printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
			get_current_time(philo->info->start), philo->id, SLP);
		sem_post(philo->info->msg);
		gettimeofday(&current_time, NULL);
		start = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		while (get_current_time(start) < philo->info->time_to_sleep)
			usleep(100);
		sem_wait(philo->info->msg);
		printf("⏳%s%ld ms \033[1;37m[%d]%s\n", CYN,
			get_current_time(philo->info->start), philo->id, THNK);
		sem_post(philo->info->msg);
	}
}

void	clear_sem(t_glob *info, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		sem_close(info->forks[i]);
	sem_close(info->msg);
}
