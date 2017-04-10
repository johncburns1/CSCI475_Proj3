/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5	//number of philosophers and forks
#define RAND_MAXIMUM	100

//TODO - locks must be declared and initialized here
mutex_t locks[N];	//default init for an array of ints is 0
mutex_t print_lock = FALSE;

/**
 * Delay for a random amount of time
 * @param alpha delay factor
 */
void	holdup(int32 alpha)
{
	long delay = rand() * alpha;
	while (delay-- > 0)
		;	//no op
}

/**
 * Eat for a random amount of time
 */
void	eat()
{
	holdup(10000);
}

/**
 * Think for a random amount of time
 */
void	think()
{
	holdup(1000);
}



/**
 * Philosopher's code
 * @param phil_id philosopher's id
 */
void	philosopher(uint32 phil_id)
{

	//TODO - right fork	
	uint32 right = phil_id;
	
	//TODO - left fork
	uint32 left;
	
	//for 1st philosopher
	if(phil_id == 0)
	{
		left = N-1;
	}
	
	//every other philosopher
	else	
	{
		left = phil_id - 1;
	}
	
	while (TRUE)
	{
		//TODO
		//think 70% of the time
		//eat 30% of the time

		double odds = (double)rand() / (double)((unsigned)RAND_MAX);

		//thinks
		if(.3 < odds && odds <= 1)
		{
			mutex_lock(&print_lock);
			kprintf("Philosopher %d thinking: zzzzzZZZz\n", phil_id);
			mutex_unlock(&print_lock);
			think();
		}
		
		//eats
		else if(0 <= odds && odds < .3)
		{
			
			//both are open
			if(locks[right] == FALSE && locks[left] == FALSE)
			{
				mutex_lock(&print_lock);
				mutex_unlock(&print_lock);
				mutex_lock(&locks[right]);
				mutex_lock(&locks[left]);
				mutex_lock(&print_lock);
				kprintf("Philosopher %d eating: nom nom nom\n", phil_id);
				mutex_unlock(&print_lock);
				eat();	
				mutex_unlock(&locks[right]);
				mutex_unlock(&locks[left]);
			}			
		} 		
	}
}

int	main(uint32 argc, uint32 *argv)
{
	//do not change
	ready(create((void*) philosopher, INITSTK, 15, "Ph1", 1, 0), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph2", 1, 1), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph3", 1, 2), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph4", 1, 3), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph5", 1, 4), FALSE);

	return 0;
}
