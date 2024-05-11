/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:57:35 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/06 17:13:15 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->lock);
	ret = philo->flag;
	pthread_mutex_unlock(&philo->lock);
	return (ret);
}

static void	*task(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->shared_lock);
	pthread_mutex_unlock(philo->shared_lock);
	pthread_mutex_lock(&philo->lock);
	philo->time_last_meal = timer(0);
	pthread_mutex_unlock(&philo->lock);
	while (1)
	{
		if (should_stop(philo))
			return (philo);
		if (philo->id % 2 == 0)
			even_eat(philo);
		else
			odd_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	return (philo);
}

int	simulate_one(char **argv)
{
	long	start;
	long	starve_time;

	start = timer(0);
	starve_time = ft_atol(argv[2]);
	printf("%lu 0 has taken a fork\n", timer(start));
	while (timer(start) < starve_time)
		;
	printf("%lu 0 died\n", timer(start));
	return (0);
}

void	simulate(t_state *state)
{
	t_philo	*philo;

	philo = state->philos;
	while (1)
	{
		pthread_create(&philo->thread_id, NULL, &task, philo);
		philo = philo->next;
		if (philo == state->philos)
			return ;
	}
	return ;
}

void	my_join(t_state *state)
{
	t_philo	*philo;

	philo = state->philos;
	while (1)
	{
		pthread_join(philo->thread_id, NULL);
		philo = philo->next;
		if (philo == state->philos)
			return ;
	}
	return ;
}
