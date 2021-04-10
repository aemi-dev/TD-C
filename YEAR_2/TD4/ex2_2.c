// © Guillaume COQUARD, April 2018


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
	int i, n, *status = (int*)malloc(sizeof(int));
	pid_t pid, p_wait;
	printf("How many child process would you create :\n");
	scanf("%d",&n);
	printf("\n");
	printf("Parent : ");
	printf("PID : %d\n",getpid());
	printf("PPID : %d\n",getppid());
	printf("PGID : %d\n",getpgid(getpid()));
	printf("\n");
	for (i = 0; i < n; i++)
	{
		if (getpid() == getpgid(getpid()))
		{
			pid=fork();
			p_wait = wait(status);
		}
		if (getpid() == getpgid(getpid())+i+1)
		{
			printf("\n");
			printf("Child #%d : ", i+1);
			printf("PID : %d\n",getpid());
			printf("PPID : %d\n",getppid());
			printf("PGID : %d\n",getpgid(getpid()));
			printf("\n");
		}
	}

	// Use of non-used variables in child process - Avoid useless WARNING
	#ifdef __linux__
	pid = pid;
	p_wait = p_wait;
	#endif

	free(status);
	return (0);
}
