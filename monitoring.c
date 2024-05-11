/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:03:10 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/06 17:04:52 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_done(t_philo *philo, t_state *state)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->lock);
	if (philo->meals == philo->info.required && !philo->done)
	{
		philo->done = DONE;
		if (++state->n_done == philo->info.n_philo)
			ret = 1;
	}
	pthread_mutex_unlock(&philo->lock);
	return (ret);
}

int	is_dead(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->lock);
	ret = timer(philo->time_last_meal) > philo->info.starve_time;
	pthread_mutex_unlock(&philo->lock);
	return (ret);
}

void	monitor(t_state *state)
{
	t_philo	*philo;

	philo = state->philos;
	state->n_done = 0;
	pthread_mutex_unlock(&state->shared_lock);
	while (1)
	{
		if (philo->info.required > 0 && all_done(philo, state))
		{
			pthread_mutex_lock(&state->shared_lock);
			return ;
		}
		if (is_dead(philo))
		{
			pthread_mutex_lock(&state->shared_lock);
			philo_print(philo, "died");
			return ;
		}
		my_sleep(100);
		philo = philo->next;
	}
}
