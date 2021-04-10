// © Guillaume COQUARD, April 2018


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>


// CONSTANTS NEEDED
#define TAILLE_MIN 10
#define SIZE_BUF 64


// FUNCTIONS NEEDED
// - Occurences counter
int count_occ(int *tab, int el, int a, int b);
// - Tab Printer
void print_tab(int *tab, int s);


int main(int argc, char **argv)
{
	int s,n,x,el,f_0[2],f_1[2];
	pid_t pid_0 = 0, pid_1 = 0;
	char buf_0[SIZE_BUF],buf_1[SIZE_BUF];
	// Use of pipes to communicate with 2 childs
	pipe(f_0);
	pipe(f_1);
	printf("Enter a tab size : \n");
	scanf("%d", &s);
	printf("Enter a minimum : \n");
	scanf("%d", &n);
	printf("Enter a maximum : \n");
	scanf("%d", &x);
	printf("Tab filled with values in %d...%d interval.\n", (n<x?n:x),(n<x?x:n));
	printf("Enter an element to find : \n");
	scanf("%d", &el);
	while (el < n || el > x) {
		printf("This value is not allowed : %d \nPlease enter an other value : \n", el);
		scanf("%d", &el);
	}
	int tab[s];
	srand(time(NULL));
	for (int i = 0; i < s; i++)
	{
		tab[i] = rand()%(n<x?x:n)+(n<x?n:x);
	}
	print_tab(tab,s);
	if (s >= TAILLE_MIN)
	{
		if (getpid() == getpgid(getpid()))
		{
			pid_0 = fork();
		}
		if (getpid() == getpgid(getpid()))
		{
			pid_1 = fork();
		}
		if (pid_0 == 0)
		{
			char *occ_0 = malloc(SIZE_BUF+1);
			close(f_0[0]);
			snprintf(occ_0,SIZE_BUF,"%d",count_occ(tab,el,0,(s%2==0?s/2:s/2+1)));
			write(f_0[1],occ_0,SIZE_BUF+1);
			exit(EXIT_SUCCESS);
		}
		else if (pid_1 == 0)
		{
			char *occ_1 = malloc(SIZE_BUF+1);
			close(f_1[0]);
			snprintf(occ_1,SIZE_BUF,"%d",count_occ(tab,el,(s%2==0?s/2:s/2+1),s));
			write(f_1[1],occ_1,SIZE_BUF+1);
			exit(EXIT_SUCCESS);
		}
		if (getpid() == getpgid(getpid()))
		{
			close(f_0[1]);
			close(f_1[1]);
			read(f_0[0],buf_0,SIZE_BUF);
			read(f_1[0],buf_1,SIZE_BUF);
			printf("Occurences of %d : %d + %d = %d\n",el,atoi(buf_0),atoi(buf_1),atoi(buf_0)+atoi(buf_1));
		}
	}
	else
	{
		printf("Occurences of %d\n", count_occ(tab,el,0,s));
	}
	return (0);
}


int count_occ(int *tab, int el, int a, int b)
{
	int occ = 0;
	for (int i = 0; i < (b>a?b-a:a-b); i++)
	{
		if (tab[a+i]==el)
		{
			occ++;
			printf("Occ : %d : index %d\n", el, i+a);
		}
	}
	return occ;
}


void print_tab(int *tab, int s)
{
	for (int i = 0; i < s; i++)
	{
		printf("%d", tab[i]);
		if (i < s-1)
		{
			printf(",");
		}
	}
	printf("\n");
}
