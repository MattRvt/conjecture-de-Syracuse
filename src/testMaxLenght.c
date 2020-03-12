#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    //longeur de tableau
    unsigned long long i = ULLONG_MAX;
    int *pointeur;
    while (1)
    {
        
        //pointeur = malloc(2^64);
        printf("size = %lld \n", i);
        //free(pointeur);
        sleep(1);
    }
    return 0;
}