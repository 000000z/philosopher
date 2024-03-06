/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 02:49:44 by adzinabi          #+#    #+#             */
/*   Updated: 2024/03/04 04:05:28 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_structure(t_data *data, char **av, int ac)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->time_philo_eat = -1;
	if (ac == 6)
		data->time_philo_eat = ft_atoi(av[5]);
}

int	is_num(char **av)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


void	thinking(t_philo *philo, int	philo_id)
{
	LOCK(&philo->data->print);
	printf("Philosopher %d is thinking.\n", philo_id);
	UNLOCK(&philo->data->print);
	usleep(200);
}

void	pick_forks(t_philo *philo, int philo_id)
{
	LOCK(&philo->right_fork);
	LOCK(philo->left_fork);
	LOCK(&philo->data->print);
	printf("Philosopher %d is picking up the forks.\n", philo_id);
	UNLOCK(&philo->data->print);
}

void	eat(t_philo *philo, int philo_id)
{
	LOCK(&philo->data->print);
	printf("Philosopher %d is eating.\n", philo_id);
	UNLOCK(&philo->data->print);
}

void	put_down_forks(t_philo *philo, int philo_id)
{

	UNLOCK(&philo->right_fork);
	UNLOCK(philo->left_fork);
	LOCK(&philo->data->print);
	printf("Philosopher %d is putting down the forks.\n", philo_id);
	UNLOCK(&philo->data->print);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	(void)philo;
	int	i = 0;
	while(i < philo->data->nbr_philo)
	{
		thinking(philo, philo->philo_id);
		pick_forks(philo, philo->philo_id);
		eat(philo, philo->philo_id);
		put_down_forks(philo, philo->philo_id);
		i++;
	}
	// LOCK(&philo->data->door);
	// printf("id: %d\n", philo->philo_id);
	// UNLOCK(&philo->data->door);
	return (NULL);
}

void	initialisation_global(t_data *data, t_philo *philo)
{
	int i = 0;
	while (i < data->nbr_philo)
	{
		pthread_create(&philo[i].th, NULL, routine, &philo[i]);
		i++;
	}	
	i = 0;
	while (i < data->nbr_philo)
		pthread_join(philo[i++].th, NULL);
}

int	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while(i < data->nbr_philo)
	{
		if(pthread_mutex_init(&philo[i].right_fork, NULL) != 0)
			return(printf("The initialisation has failed : right_fork"), 0);
		if(data->time_philo_eat != -1)
		{
			if(pthread_mutex_init(&philo[i].nbr_of_meal_eaten, NULL) != 0)
				return(printf("The initialisation has failed : nbr_of_meal_eaten"), 0);
		}
		philo[i].philo_id = i + 1;
		philo[i].data = data;
		if (i != data->nbr_philo - 1)
			philo[i].left_fork = &philo[i + 1].right_fork;
		else
			philo[i].left_fork = &philo[0].right_fork;
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	static t_data	data;
	t_philo			*philo;

	if (ac == 5 || ac == 6)
	{
		if (is_num(av) == 0)
			return (1);
		init_structure(&data, av, ac);
		philo = malloc(sizeof(t_philo) * data.nbr_philo);
		if(!philo)
			return(1);
		data.philo = philo;
		init_philo(&data, philo);
		initialisation_global(&data, philo);
	}
	else
		return (printf("Too many or not enough arguments\n"), 1);
	if (data.nbr_philo == 1)
	{
		// un_philo(philo);
		return(1);
	}
	free(philo);
}
