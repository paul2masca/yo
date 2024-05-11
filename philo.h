/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:56:16 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/06 17:15:21 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define DONE 1
#define NOT_DONE 0

#define ERROR_VAL -1

typedef struct s_philo	t_philo;

typedef struct s_info
{
	long				n_philo;
	long				starve_time;
	long				eat_time;
	long				sleep_time;
	long				required;
	long				start;
}						t_info;
typedef struct s_philo
{
	pthread_mutex_t		lock;
	pthread_t			thread_id;
	t_info				info;
	pthread_mutex_t		*shared_lock;
	int					id;
	int					meals;
	int					flag;
	int					done;
	long				time_last_meal;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	t_philo				*next;
	t_philo				*prev;
}						t_philo;

typedef struct s_state
{
	t_philo				*philos;
	pthread_mutex_t		shared_lock;
	long				n_done;
}						t_state;

// utils.c
void					my_sleep(long time);
long					timer(long start);
int						check_input(int argc, char **argv);
void					philo_print(t_philo *philo, char *msg);
void					set_stop_flags(t_state *state);

// ft_atol.c
long					ft_atol(char *str);

// setup.c
void					set_info(t_philo *philo, char **argv);
t_state					*full_setup(t_state *state, char **argv);
void					delete(t_state *state);

// actions.c
void					philo_print(t_philo *philo, char *msg);
void					philo_think(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					even_eat(t_philo *philo);
void					odd_eat(t_philo *philo);

// simulation.c
int						simulate_one(char **argv);
void					simulate(t_state *state);
void					my_join(t_state *state);

// monitoring.c
void					monitor(t_state *state);
