/**
 * - amélioration espéré: faire marcher le programme pour 1,2,4,8,16,3,-1
 * - amélioration effective:
 * - temps d'exécution pour 77777: 
 *
 *  
*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int tab[3000];

void conjectureIsDemontre(int resultat){
    if (resultat == 1){
        printf("la conjecture est démontré. le resultat = %d", resultat);
    } else {
        printf("la conjecture n'est pas démontré. le résultat = %d", resultat)
    }
}

int main(){
    

  return 0;
}
