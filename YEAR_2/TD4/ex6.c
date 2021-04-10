// © Guillaume COQUARD, April 2018


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// CONSTANTS NEEDED
#define SIZE 256


// FUNCTIONS NEEDED
// - add function from TD2
char *add(const char *dir, const char *name);
// - find function based on ex3_TD2
int find(char *el, char *path);


int main(int argc, char **argv)
{
	if (argc!=3)
	{
		find("-all",".");
	}
	else
	{
		find(argv[1],argv[2]);
	}
	return (0);
}


char *add(const char *dir, const char *name)
{
	char *ref = malloc((strlen(dir) + strlen(name) + strlen("/"))+1);
	strcpy(ref, dir);
	strcat(ref, "/");
	strcat(ref, name);
	return ref;
}


int find(char *el, char *path)
{
	DIR *dir = NULL;
	struct dirent *file = NULL;

	if ((dir=opendir(path))==NULL)
	{
		perror("Failed ");
		return (-1);
	}

	while ((file = readdir(dir)) != NULL)
	{
		pid_t pid = 1, p_wait_p, p_wait_c;
		char *name = malloc(SIZE*sizeof(char)+1);
		strcpy(name,file->d_name);
		int *s_p = (int*)malloc(sizeof(int));
		int *s_c = (int*)malloc(sizeof(int));

		char v2[1] = ".";
		if (name[0]!=v2[0] || ((strlen(name)==2)&&(name[0]==v2[0])&&(name[1]!=v2[0])) || (strlen(name)>2))
		{
			if ((strcmp(el,name) == 0) || (strcmp(el,"-all") == 0))
			{
				printf("%s \n", add(path,name));
			}
			if (file->d_type == DT_DIR)
			{
				if ((pid = fork()) == 0)
				{
					find(el,add(path,name));
				}
				else if (getpid() != getpgid(getpid()) && pid > 0) // When child -> wait child of child
				{
					p_wait_c = wait(s_c);
				}
				else if (getpid() == getpgid(getpid())) // When Main Parent -> wait child
				{
					p_wait_p = wait(s_p);
				}
			}
		}
		if (getpid() == getpgid(getpid()))
		{
			free(s_p);
		}
		else if (pid > 0)
		{
			free(s_c);
		}

		// Use of non-used variables in child process - Avoid useless WARNING
		#ifdef __linux__
		p_wait_c = p_wait_c;
		p_wait_p = p_wait_p;
		#endif

	}
	closedir(dir);
	exit(EXIT_SUCCESS);
}
