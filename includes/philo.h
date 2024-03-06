/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 02:45:09 by adzinabi          #+#    #+#             */
/*   Updated: 2024/03/06 18:12:44 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# define LOCK(x) pthread_mutex_lock(x) 
# define UNLOCK(x) pthread_mutex_unlock(x) 

typedef struct t_data t_data;

typedef struct t_philo {
    int             philo_id;
    pthread_t       th;
    long long       what_time_is_it;
    long long       last_meal;
    pthread_mutex_t	nbr_of_meal_eaten;
    pthread_mutex_t right_fork;
    pthread_mutex_t *left_fork;
    t_data          *data;
}   t_philo;

typedef struct t_data {
    int         nbr_philo; 
    int         time_die;
    int         time_eat;
    int         time_sleep;
    int         time_philo_eat;
    int         nbr_of_forks;
    pthread_mutex_t print;
    t_philo     *philo;
}   t_data;

int	    ft_atoi(const char *str);
int     init_philo(t_data *data, t_philo *philo);
void	initialisation_global(t_data *data, t_philo *philo);
void	*routine(void *arg);
int     is_num(char **av);
void    init_structure(t_data *data, char **av, int ac);
void	tempo(long int time_in_ms, t_philo *philo);

#endif