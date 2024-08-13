#include "philo.h"

void	*death_checker_thread(void *data)
{
	t_philo *p;

	p = (t_philo *)data;
	while (p->monitor->die > get_ms() - p->last_meal_time)
	{
		usleep(1000);
		//end simulation
	}
	if (!(p->eating))
	{
		p->death_flag = true;
		state_message(p->monitor->beginning, DIE, p);
		p->monitor->end_flag = true;
	}

	return (NULL);
}