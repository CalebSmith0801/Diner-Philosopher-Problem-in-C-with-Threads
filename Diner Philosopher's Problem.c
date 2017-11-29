#include "windows.h" //For Sleep()
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LEFT (n + 4) % 5
#define RIGHT (n + 1) % 5

pthread_t philosopher[5];
pthread_mutex_t chopstick[5]; 

void *Eat(int n) {
	printf ("Philosopher %d is thinking\n" , n+1);

	Sleep(50);

	pthread_mutex_lock(&chopstick[LEFT]);  //philospher uses the chopsticks
	pthread_mutex_lock(&chopstick[RIGHT]); //to the left and right of them
	printf("Philosopher %d grabbed chopstick %d & %d\n", n+1, LEFT+1, RIGHT+1);
	printf("Philosopher %d is eating\n", n+1);

	Sleep(50);

	pthread_mutex_unlock(&chopstick[n]);    //Puts chopsticks back down
	pthread_mutex_unlock(&chopstick[(n+1)%5]);
	printf("Philosopher %d finished eating\n", n+1);

	return(NULL);
}

int main(){
	int j;						//For the sake of making the program finish
	for (j = 0; j < 5; j++){    //each philospher only eats 5 times
		int i;
		for(i = 0; i < 5; i++)
			pthread_mutex_init(&chopstick[i], NULL); //Initializes threads for available chopsticks
		
		for(i = 0; i < 5; i++)
			pthread_create(&philosopher[i], NULL, (void *)Eat, (void *)i); //Creates threads for philosphers and calls function
		
		for(i = 0; i < 5; i++)
			pthread_join(philosopher[i], NULL);  //Waits for all thread to exit
		
		for(i = 0; i<5; i++)
			pthread_mutex_destroy(&chopstick[i]); //Destorys all the threads
		printf("\n");
	}
	return 0;
}

/*Output
Philosopher 1 is thinking
Philosopher 3 is thinking
Philosopher 2 is thinking
Philosopher 5 is thinking
Philosopher 4 is thinking
Philosopher 4 grabbed chopstick 3 & 5
Philosopher 4 is eating
Philosopher 3 grabbed chopstick 2 & 4
Philosopher 3 is eating
Philosopher 2 grabbed chopstick 1 & 3
Philosopher 2 is eating
Philosopher 3 finished eating
Philosopher 4 finished eating
Philosopher 2 finished eating
Philosopher 1 grabbed chopstick 5 & 2
Philosopher 1 is eating
Philosopher 1 finished eating
Philosopher 5 grabbed chopstick 4 & 1
Philosopher 5 is eating
Philosopher 5 finished eating

Philosopher 1 is thinking
Philosopher 2 is thinking
Philosopher 3 is thinking
Philosopher 4 is thinking
Philosopher 5 is thinking
Philosopher 2 grabbed chopstick 1 & 3
Philosopher 2 is eating
Philosopher 1 grabbed chopstick 5 & 2
Philosopher 1 is eating
Philosopher 2 finished eating
Philosopher 5 grabbed chopstick 4 & 1
Philosopher 5 is eating
Philosopher 1 finished eating
Philosopher 4 grabbed chopstick 3 & 5
Philosopher 4 is eating
Philosopher 5 finished eating
Philosopher 4 finished eating
Philosopher 3 grabbed chopstick 2 & 4
Philosopher 3 is eating
Philosopher 3 finished eating

Philosopher 1 is thinking
Philosopher 2 is thinking
Philosopher 3 is thinking
Philosopher 4 is thinking
Philosopher 5 is thinking
Philosopher 1 grabbed chopstick 5 & 2
Philosopher 1 is eating
Philosopher 2 grabbed chopstick 1 & 3
Philosopher 2 is eating
Philosopher 5 grabbed chopstick 4 & 1
Philosopher 5 is eating
Philosopher 1 finished eating
Philosopher 2 finished eating
Philosopher 5 finished eating
Philosopher 4 grabbed chopstick 3 & 5
Philosopher 4 is eating
Philosopher 4 finished eating
Philosopher 3 grabbed chopstick 2 & 4
Philosopher 3 is eating
Philosopher 3 finished eating

Philosopher 1 is thinking
Philosopher 3 is thinking
Philosopher 4 is thinking
Philosopher 5 is thinking
Philosopher 2 is thinking
Philosopher 1 grabbed chopstick 5 & 2
Philosopher 1 is eating
Philosopher 5 grabbed chopstick 4 & 1
Philosopher 5 is eating
Philosopher 1 finished eating
Philosopher 5 finished eating
Philosopher 4 grabbed chopstick 3 & 5
Philosopher 4 is eating
Philosopher 3 grabbed chopstick 2 & 4
Philosopher 3 is eating
Philosopher 4 finished eating
Philosopher 3 finished eating
Philosopher 2 grabbed chopstick 1 & 3
Philosopher 2 is eating
Philosopher 2 finished eating

Philosopher 1 is thinking
Philosopher 2 is thinking
Philosopher 3 is thinking
Philosopher 4 is thinking
Philosopher 5 is thinking
Philosopher 1 grabbed chopstick 5 & 2
Philosopher 1 is eating
Philosopher 2 grabbed chopstick 1 & 3
Philosopher 2 is eating
Philosopher 5 grabbed chopstick 4 & 1
Philosopher 5 is eating
Philosopher 1 finished eating
Philosopher 2 finished eating
Philosopher 4 grabbed chopstick 3 & 5
Philosopher 4 is eating
Philosopher 5 finished eating
Philosopher 4 finished eating
Philosopher 3 grabbed chopstick 2 & 4
Philosopher 3 is eating
Philosopher 3 finished eating
*/