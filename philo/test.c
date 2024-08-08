
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>

int num = 0;
pthread_mutex_t lock;


void*	routine()
{
	pthread_mutex_lock(&lock);
	num++;
	pthread_mutex_unlock(&lock);
}
int main()
{
	int i = 0;
	pthread_t threads[3];
	// pthread_t	a, b;
	pthread_mutex_init(&lock, NULL);

	// pthread_create(&a, NULL, &routine, NULL);

	// pthread_create(&b, NULL, &routine, NULL);

	// pthread_join(a, NULL);

	// pthread_join(b, NULL);

	while (i < 3)
	{
		pthread_create(&threads[i], NULL, &routine, NULL);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&lock);
	printf("value: %d\n", num);
	return (0);
}