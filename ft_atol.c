/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:23:51 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/02 18:56:45 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	is_digit(char c)
{
	return (c <= '9' && c >= '0');
}

long	ft_atol(char *str)
{
	long	num;

	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (ERROR_VAL);
	if (!is_digit(*str))
		return (ERROR_VAL);
	num = 0;
	while (is_digit(*str))
	{
		num = (num * 10) + (*str++ - '0');
		if (num > INT_MAX)
			return (ERROR_VAL);
	}
	return (num);
}
