/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:18:04 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/02 20:29:33 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_state	state;

	if (!check_input(argc, argv))
		return (1);
	if (ft_atol(argv[1]) == 1)
		return (simulate_one(argv));
	state.philos = NULL;
	state.n_done = 0;
	pthread_mutex_init(&state.shared_lock, NULL);
	pthread_mutex_lock(&state.shared_lock);
	if (full_setup(&state, argv) == NULL)
	{
		pthread_mutex_unlock(&state.shared_lock);
		pthread_mutex_destroy(&state.shared_lock);
		return (1);
	}
	simulate(&state);
	monitor(&state);
	set_stop_flags(&state);
	pthread_mutex_unlock(&state.shared_lock);
	my_join(&state);
	delete(&state);
	return (0);
}
