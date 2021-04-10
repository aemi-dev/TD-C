#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_WAIT_S 3
#define NB_THREAD 4
#define TARGET 10

struct shared_counter {
	int count;
	pthread_mutex_t lock;
	int target;
};

void* count( void* _param) {

	struct shared_counter* param;
	unsigned int seed;
	pthread_t id;
	
	param = (struct shared_counter*) _param;
	id = pthread_self();
	seed = time(NULL) + id;
	
	
	do {

		sleep( rand_r( &seed) % MAX_WAIT_S);

		pthread_mutex_lock(&param->lock);
		if ( param->count != param->target) 
		{
			param->count += 1;
			printf("Valeur courante : %d, dans %u\n", param->count, id);
			if ( param->count == param->target )
			{
				printf("Je suis le vainqueur (%u).\n", id);
			}
		}
		else {
			pthread_mutex_unlock(&param->lock);
			break;
		}	
		
		pthread_mutex_unlock(&param->lock);
	} while (1);
	

	pthread_exit(NULL);

}

int main( int argc, char ** argv )
{
	pthread_t id[NB_THREAD];
	struct shared_counter clock;
	int i;

	clock.count = 0;
	clock.target = TARGET;

	if (pthread_mutex_init( &(clock.lock), NULL) )
	{
		fprintf(stderr,"Something went wrong while reserving a mutex...\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < NB_THREAD; i++) {
		int rc;
		rc = pthread_create( &id[i], NULL, count, &clock);
	       if (rc) {
		       fprintf(stderr,"Something went wrong with POSIX thread creation...\n");
		       exit(EXIT_FAILURE);
	       }
	}

	for (i = 0; i < NB_THREAD ; i++) {
		int rc;
		rc = pthread_join( id[i], NULL);
		if (rc) {
			fprintf(stderr,"Something went wront while joining threads...\n");
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}
