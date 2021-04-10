// © Guillaume COQUARD, April 2018


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
	pid_t pid, p_wait;
	int *status = (int*)malloc(sizeof(int));
	pid = fork();
	switch (pid)
	{
		case -1:
		perror("fork ");
		break;
		case 0:
		printf("PROCESS :\n");
		printf("State : Child\n");
		printf("PID : %d\n",getpid());
		printf("PPID : %d\n",getppid());
		printf("PGID : %d\n",getpgid(getpid()));
		printf("\n");
		break;
		default:
		printf("PROCESS :\n");
		printf("State : Parent\n");
		printf("PID : %d\n",getpid());
		printf("PPID : %d\n",getppid());
		printf("PGID : %d\n",getpgid(getpid()));
		if (pid)
		{
			printf("Child : %d\n", pid);
		}
		printf("\n");
		p_wait = wait(status);
		break;
	}

	// Use of non-used variables in child process - Avoid useless WARNING
	#ifdef __linux__
	p_wait = p_wait;
	#endif

	free(status);
	return (0);
}
