// © Guillaume COQUARD, April 2018


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// FUNCTIONS NEEDED
int multiFork(int n);
int multiFork_wait(int n);


int main()
{
	int n;
	printf("How many child process would you create :\n");
	scanf("%d",&n);
	multiFork_wait(n);
	return (0);
}


int multiFork(int n)
{
	int i;
	pid_t pid;
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
	#endif

	return (EXIT_SUCCESS);
}


int multiFork_wait(int n)
{
	int i, *status = (int*)malloc(sizeof(int));
	pid_t pid, p_wait;
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
		}
		if (getpid() == getpgid(getpid())+i+1)
		{
			printf("\n");
			printf("Child #%d : ", i+1);
			printf("PID : %d\n",getpid());
			printf("PPID : %d\n",getppid());
			printf("PGID : %d\n",getpgid(getpid()));
			return (SIGCHLD);
		}
		if (getpid() == getpgid(getpid()))
		{
			do {
				if ((p_wait = waitpid(pid, status, WUNTRACED)) == -1)
				{
					perror("Failed ");
					exit(EXIT_FAILURE);
				}
				if (WIFEXITED(*status))
				{
					printf("Child process exited : Status : %d\n", (int)WEXITSTATUS(*status));
				}
				else if (WIFSIGNALED(*status))
				{
					printf("Child process killed : Signal : %d\n", (int)WTERMSIG(*status));
				}
				else if (WIFSTOPPED(*status))
				{
					printf("Child process stopped : Signal : %d\n", (int)WSTOPSIG(*status));
				}
				else
				{
					printf("Child process encountered an unexpected status.\nStatus : %x\n", *status);
				}
			} while (!WIFEXITED(*status) && !WIFSIGNALED(*status));
			printf("\n");
		}
	}
	free(status);
	return (EXIT_SUCCESS);
}
