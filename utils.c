/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:12:10 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/06 17:14:51 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (0);
	while (--argc > 0)
	{
		if (ft_atol(argv[argc]) == ERROR_VAL)
			return (0);
	}
	return (1);
}

long	timer(long start)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start);
}

void	my_sleep(long time)
{
	long	start;

	start = timer(0);
	while (timer(start) < time)
	{
		usleep(10);
	}
}

void	philo_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->lock);
	if (!philo->flag)
		printf("%lu %d %s\n", timer(philo->info.start), philo->id, msg);
	pthread_mutex_unlock(&philo->lock);
}

void	set_stop_flags(t_state *state)
{
	t_philo	*philo;

	philo = state->philos;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		philo->flag = 1;
		pthread_mutex_unlock(&philo->lock);
		philo = philo->next;
		if (philo == state->philos)
			return ;
	}
}
