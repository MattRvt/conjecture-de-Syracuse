/**
 * - amélioration espéré: faire marcher le programme pour 1,2,4,8,16,3,-1
 * - amélioration effective:
 * - temps d'exécution pour 77777:
 *
 *
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <pthread.h>
#define NB_THREAD 5000

pthread_attr_t attr;

unsigned long long MAX = ULLONG_MAX;
long int tab[INT_MAX][2];

/*
    -   tab :   -
  colone 1 : possède la valeur le l'étape d'après
  colone 2 : possède le n° d'etape pour aller à 1
  colone 3 : dis si l'étape a déjà été faite ou non par un autre thread

*/

//int valfin = 2147483647;

void *conject(void * arg);

int main() {

  //long int valdebut = atoi(argv[1]);
  pthread_t thr[NB_THREAD];

  pthread_attr_init(& attr);
  pthread_attr_setdetachstate(& attr, PTHREAD_CREATE_DETACHED);
  printf("debut\n" );
  //if(valdebut > 0 && argc > 1){
    if(pthread_create(&thr[1],&attr,conject,(void *)2) != 0)
      fprintf(stderr, "Erreur dans pthread\n");


  sleep(2);
  printf("fin prog\n" );
  return 0;
}

void * conject(void * arg){
  long int val = (long int) arg;
  tab[val][2] = 1;
  int etape = tab[val][1];
  pthread_t t1, t2, t3;
  if(tab[val*2][3] != 1){
    if( pthread_create(&t1, &attr, conject, (void *)(val*2)) != 0)
      fprintf(stderr, "Erreur dans un thread\n" );

    }
  if((val-1 %3) == 0){
    if(tab[(val-1)/3][3] != 1)
      if( pthread_create(&t2, &attr, conject, (void *)(val-1 %3)) != 0)
        fprintf(stderr, "Erreur dans un thread\n" );

    }
  if(tab[val+1][3] != 1){
    if( pthread_create(&t3, &attr, conject, (void *)(val+1)) != 0)
      fprintf(stderr, "Erreur dans un thread\n" );

    }
  printf("n°etape : %ld.  %ld -> %ld\n",tab[val][0], val, tab[val][1]);

}
