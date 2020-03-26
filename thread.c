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
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned long long MAX = ULLONG_MAX;
long int tab[INT_MAX][2];

/*
    -   tab :   -
  colone 0 : possède la valeur le l'étape d'après
  colone 1 : possède le n° d'etape pour aller à 1
  colone 2 : dis si l'étape a déjà été faite ou non par un autre thread

*/

//int valfin = 2147483647;

void *conject(void * arg);

int conjectrec(long int val, int etape){
  if(val%2==0)
    return conjectrec(val/2, etape+1);
  if(val==1)
    return 1;
  else
    return conjectrec(val*3 +1, etape+1);
}

int main() {

  //long int valdebut = atoi(argv[1]);
  pthread_t thr[NB_THREAD];

  pthread_attr_init(& attr);
  pthread_attr_setdetachstate(& attr, PTHREAD_CREATE_DETACHED);
  printf("debut\n" );
  //if(valdebut > 0 && argc > 1){
  tab[2][0] = 1;
  if(pthread_create(&thr[1],&attr,conject,(void *)2) != 0)
    fprintf(stderr, "Erreur dans pthread\n");


  sleep(2);
  pthread_mutex_lock(&mutex);
  
  printf("fin prog\n" );
  exit(0);

}

void * conject(void * arg){
  pthread_mutex_lock(&mutex);
  long int val = (long int) arg;
  tab[val][2] = 1;
  int etape = tab[val][1];
  pthread_t t1, t2, t3;

  //sleep(1);


      if(val<100 /*&& val*2 < 100*/){
        if(tab[val*2][2] != 1){
          tab[val*2][0] =  tab[val][0] + 1;
          if( pthread_create(&t1, &attr, conject, (void *)(val*2)) != 0)
            fprintf(stderr, "Erreur dans un thread\n" );
        }

          
        if((val-1 %3) == 0 && tab[(val-1)/3][2] != 1){
            tab[(val-1)/3][0] =  tab[val][0] + 1;
            if( pthread_create(&t2, &attr, conject, (void *)((val-1) /3)) != 0)
              fprintf(stderr, "Erreur dans un thread\n" );
        }

          
        if(tab[val+1][2] != 1){
          tab[val+1][0] = conjectrec(val+1, 0) ;
          if( pthread_create(&t3, &attr, conject, (void *)(val+1)) != 0)
            fprintf(stderr, "Erreur dans un thread\n" );
        }
        

        if(val%2==0)
          tab[val][1] = val/2;
        else
          tab[val][1] = val*3 +1;


        printf("nb etape : %ld.  %ld -> %ld\n",tab[val][0], val, tab[val][1]);
      }
  pthread_mutex_unlock(&mutex);


}