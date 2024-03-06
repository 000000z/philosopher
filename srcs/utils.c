/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 02:49:37 by adzinabi          #+#    #+#             */
/*   Updated: 2024/03/06 18:12:17 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	base;

	i = 0;
	sign = 1;
	base = 0;
	while (str[i] && (str[i] == ' '))
	{
		i += 1;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && base < 2147483647 && base > -2147483648)
	{
		base = base * 10 + (str[i] - '0');
		i++;
	}
	return (base * sign);
}

void	tempo(long int time_in_ms, t_philo *philo)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(100);
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}