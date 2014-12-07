#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "csapp.h"
int counter = 1;
void doit()
{
    fork();
    fork();
    printf("hello\n");
    return;
}

void doit2()
{
    if(fork()==0)
    {
    fork();
    printf("hello \n");
    exit(0);

    }
    return;

}

int main()
{
    /*printf("8.12 \n");
    doit();
    printf("hello\n");
    printf("\n");
    exit(0);
    */
/*
    printf("8.14 \n");
    doit2();
    printf("hello \n");

*/

    if(fork()==0)
    {
        counter--;
        exit(0);


    }
    else
    {
    wait(NULL);
    printf("counter = %d\n", ++counter);
    }
    exit(0);
}
