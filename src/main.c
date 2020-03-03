#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NB_THREAD 6

int tab[3000];

void conjectureIsDemontre(int resultat){
    if (resultat == 1){
        printf("la conjecture est démontré. le resultat = %d", resultat);
    } else {
        printf("la conjecture n'est pas démontré. le résultat = %d", resultat)
    }
}

int maint(){
    
    
  return 0;
}
