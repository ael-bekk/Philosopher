/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk <ael-bekk@student.13    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:58:28 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/03/13 17:41:45 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosofers.h"

int	args_control(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("wrong args\n");
		return (1);
	}
	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j] && av[i][j] >= '0' && av[i][j] <= '9')
			j++;
		if (ft_atoi(av[i]) <= 0 || av[i][j])
		{
			printf("wrong args\n");
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	int				nb_philos;
	t_philo			*philos;
	t_glob			*info;

	if (args_control(ac, av))
		return (1);
	nb_philos = ft_atoi(av[1]);
	philos = malloc(sizeof(t_philo) * nb_philos);
	info = malloc(sizeof(t_glob));
	if (!philos || !info)
		return (1);
	info->forks = malloc(sizeof(sem_t *) * nb_philos);
	if (!info->forks)
		return (1);
	info->nb_philos = nb_philos;
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->number_of_times = -1;
	if (ac == 6)
		info->number_of_times = ft_atoi(av[5]);
	creat_prosses(philos, info);
	watch_prosses(philos);
	clear_sem(info, nb_philos);
	return (1);
}
