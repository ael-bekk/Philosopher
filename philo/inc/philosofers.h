/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk <ael-bekk@student.13    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:57:42 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/03/02 14:09:00 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H

# define TRUE 1
# define FALSE 0

# define NRM  "\x1B[0m"
# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"
# define MAG  "\x1B[35m"
# define CYN  "\x1B[36m"
# define WHT  "\x1B[37m"

# define R_FRK  ":  \x1B[33mhas taken a right fork ✋🍴\x1B[0m"
# define L_FRK  ":  \x1B[33mhas taken a left fork 🍴🤚\x1B[0m"
# define EAT  ":  \x1B[35mis eating  🍔🍟\x1B[0m"
# define SLP  ":  \x1B[34mis sleeping 😴\x1B[0m"
# define THNK  ":  \x1B[36mis thinking 🤔\x1B[0m"
# define DIED  ":  \033[1;91m is dead 💀\x1B[0m"
# define FINISH  ":  \x1B[32msimulation is finished 💯\x1B[0m"

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_glob
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times;
	long			start;
	pthread_mutex_t	msg;
	pthread_mutex_t	*forks;
}	t_glob;

typedef struct s_philo
{
	int				id;
	int				number_of_times;
	long			last_eat;
	pthread_t		philo;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_glob			*info;
}	t_philo;

/////////////////////       utils     ///////////////////////
int		ft_atoi(const char *str);

/////////////////////       creat_thread     ///////////////////////
void	creat_threads(t_philo *philos, t_glob *info);

/////////////////////       watcher_thread     ///////////////////////
int		watch_threads(t_philo *philos);
int		exit_threads(int ex, t_philo *philo);

/////////////////////       routine     ///////////////////////
void	philo_eating(t_philo *philo);
void	*philo_routin(void *p);
void	clear_mutex(pthread_mutex_t *m, int size);

/////////////////////       args_control     ///////////////////////
int		args_control(int ac, char **av);

long	get_current_time(long start);

#endif