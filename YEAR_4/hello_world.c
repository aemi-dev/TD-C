#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct message {
	pthread_t* index;
	char *chaine;
};


void *print_hello( void* _param )
{

	struct message* param = (struct message*)_param;

	printf("%s : %#u\n", param->chaine, *param->index);
	pthread_exit(NULL);
}

int main( int argc, char ** argv )
{
	pthread_t process[15];
	struct message param[15];

	int i;

	for ( i = 0 ; i < 15 ; i++ ) {
		int rc;
		
		param[i].chaine = "Mon message est beau";
		param[i].index = &process[i];

		rc = pthread_create( &process[i], NULL, print_hello, (void*)&param[i]);
		if (rc) {
			fprintf(stderr,"Un petit soucis à la création du thread...\n");
			exit(EXIT_FAILURE);
		}
	}

	for ( i = 0 ; i < 15 ; i++ ) {
		int rc;

		rc = pthread_join( process[i], NULL );

		if (rc) {
			fprintf(stderr,"Un petit soucis au join...\n");
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);

}
