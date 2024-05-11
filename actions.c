/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:03:10 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/06 17:04:52 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_lock);
	philo_print(philo, "is thinking");
	pthread_mutex_unlock(philo->shared_lock);
	return ;
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->shared_lock);
	philo_print(philo, "is sleeping");
	pthread_mutex_unlock(philo->shared_lock);
	my_sleep(philo->info.sleep_time);
	return ;
}

void	eat_update(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	++philo->meals;
	philo->time_last_meal = timer(0);
	pthread_mutex_unlock(&philo->lock);
}

void	even_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->shared_lock);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	pthread_mutex_unlock(philo->shared_lock);
	eat_update(philo);
	my_sleep(philo->info.eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}

void	odd_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->shared_lock);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	pthread_mutex_unlock(philo->shared_lock);
	eat_update(philo);
	my_sleep(philo->info.eat_time);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return ;
}
