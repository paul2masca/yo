/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:57:30 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/02 20:08:56 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_philo(t_state *state, t_philo *philo)
{
	t_philo	*last;

	if (!state->philos)
	{
		philo->next = philo;
		philo->prev = philo;
		state->philos = philo;
	}
	else
	{
		last = (state->philos)->prev;
		last->next = philo;
		philo->prev = last;
		philo->next = state->philos;
		last->right_fork = philo->left_fork;
		philo->right_fork = state->philos->left_fork;
		state->philos->prev = philo;
	}
}

void	delete(t_state *state)
{
	t_philo	*philo;
	t_philo	*next_philo;

	philo = state->philos;
	pthread_mutex_destroy(&state->shared_lock);
	while (1)
	{
		next_philo = philo->next;
		pthread_mutex_destroy(philo->left_fork);
		pthread_mutex_destroy(&philo->lock);
		free(philo->left_fork);
		free(philo);
		philo = next_philo;
		if (philo == state->philos)
			return ;
	}
}

void	set_info(t_philo *philo, char **argv)
{
	philo->info.start = timer(0);
	philo->info.n_philo = ft_atol(argv[1]);
	philo->info.starve_time = ft_atol(argv[2]);
	philo->info.eat_time = ft_atol(argv[3]);
	philo->info.sleep_time = ft_atol(argv[4]);
	if (argv[5])
		philo->info.required = ft_atol(argv[5]);
	else
		philo->info.required = ERROR_VAL;
	philo->info.start = timer(0);
}

t_philo	*create_philo(t_state *state, char **argv)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->left_fork)
	{
		free(philo);
		return (NULL);
	}
	pthread_mutex_init(philo->left_fork, NULL);
	set_info(philo, argv);
	pthread_mutex_init(&philo->lock, NULL);
	philo->meals = 0;
	philo->done = 0;
	philo->flag = 0;
	philo->time_last_meal = timer(0);
	philo->shared_lock = &(state->shared_lock);
	return (philo);
}

t_state	*full_setup(t_state *state, char **argv)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < (int)ft_atol(argv[1]))
	{
		philo = create_philo(state, argv);
		if (!philo)
			return (NULL);
		philo->id = i;
		add_philo(state, philo);
	}
	return (state);
}
