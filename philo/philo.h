#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>

# define RED "\033[31m"      // Red text
# define GREEN "\033[32m"    // Green text
# define YELLOW "\033[33m"   // Yellow text
# define BLUE "\033[34m"     // Blue text
# define MAGENTA "\033[35m"  // Magenta text
# define CYAN "\033[36m"     // Cyan text
# define WHITE "\033[37m"    // White text
#define RST "\033[0m"     // Resets all text attributes

typedef struct s_philo
{
	//last meal
	int		index;
	long	last_meal_time;
	int		meal_counter;

}	t_philo;

typedef struct s_monitor
{
	int	num_of_philos;
	int	time_of_eating;
	int	sleep;
	int	die;
}	t_monitor;



int		check_args(char **argv);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	error(char *message);



#endif