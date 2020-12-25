#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "common.h"

int main ( int argc, char *argv[] ) {

    if (argc != 2)
    {
        printf("Invalid Input \n");
        exit(1);
    }

    int *p;

    p = malloc (sizeof(int));
    assert(p!= NULL);

    printf("(%d) address of pointer to by p: %p \n", (int) getpid(), p);

    *p =  atoi (argv[1]); // assign value to address stored in p

    while(1)
    {
        Spin(1);
        *p = *p + 1;
        printf("(%d value of p: %p \n)", (int) getpid(), p);
    }
}
