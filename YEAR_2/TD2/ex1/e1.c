#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define EXERCISE "Exercise 1 : Parcours iteratif et recursif d'un tableau"
#define MIN 1
#define MAX 5



// NEEDED FUNTIONS
//  -- affiche_tab -- a : array -- b : size
void a_t(int a[], int b);
//  -- somme_iter -- a : array -- b : size
int is_t(int a[], int b);
//  -- somme_rec -- a : array -- b : index
int rs_t(int a[], int b);



// PERSONNAL FUNCTIONS
//  -- print any text + any separator
void prt_t(char a[], char b[]);
//  -- print any int||long + any separator
void prt_n(long a, char b[]);
//  -- Random Number Generator
int  rng(int a, int b, int c);



int main() {
    prt_t(EXERCISE,"\n\n");

	prt_t("Enter an array size :"," ");
    int a; scanf("%d", &a);

    int b[a];
    for (int i = 0; i < a; i++) {
        b[i] = rng(MIN,MAX,i);
    }

    a_t(b,a);
    prt_n(is_t(b,a),"\n");
    prt_n(rs_t(b,a-1),"\n\n");

    return (0);
}



void prt_t(char a[],char b[]) {
    printf("%s%s",a,b);
}
void prt_n(long a,char b[]) {
    printf("%ld%s",a,b);
}
int rng(int a,int b,int c) {
    srand(c+time(NULL)); // execution time is too short to simply use time(NULL), so we increment it with index c
    return (rand()%b + 1);
}



void a_t(int a[],int b) {
    for (int i = 0; i < b; i++) {
        i!=b-1?prt_n(a[i]," "):prt_n(a[i],"\n");
    }
}
int is_t(int a[],int b) {
	int c=0;
	for (int i=0;i<b;i++) {
        c+=a[i];
    }
    return c;
}
int rs_t(int a[],int b) {
    return b<0?0:a[b]+rs_t(a,b-1);
}
