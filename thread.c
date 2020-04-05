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
#define ok 1

pthread_attr_t attr;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long int tab[INT_MAX][2];

/*
    -   tab :   -
  colone 0 : possède la valeur le l'étape d'après
  colone 1 : possède le n° d'etape pour aller à 1
  colone 2 : dis si l'étape a déjà été faite ou non par un autre thread

*/


void *conject(void * arg);

int conjectrec(long int val, int etape){
  if(val%2==0)
    return conjectrec(val/2, etape+1)+1;
  if(val==1)
    return 1;
  else
    return conjectrec(val*3 +1, etape+1)+1;
}

int main() {

  pthread_t thr[NB_THREAD];

  pthread_attr_init(& attr);
  pthread_attr_setdetachstate(& attr, PTHREAD_CREATE_DETACHED);
  printf("debut\n" );
  //if(valdebut > 0 && argc > 1){
  tab[1][0] = 1;
  if(pthread_create(&thr[1],&attr,conject,(void *)1) != 0)
    fprintf(stderr, "Erreur dans pthread\n");


  sleep(2);
  printf("fin prog\n" );
  pthread_mutex_lock(&mutex);
  for(int i = 2; i <100; i++)
    printf("%ld. %d -> %ld\n", tab[i][0], i, tab[i][1]);
  exit(0);

}



void * conject(void * arg)  {
  long int val = (long int) arg;
  if(tab[val][2] != 0)
    pthread_exit(NULL);
  pthread_mutex_lock(&mutex);
  //printf("val : %ld déjà fait : %ld \n", val, tab[val][2]);
  
      if(val<200){

        tab[val][2] = ok;
        pthread_t t1, t2, t3;

        if(tab[val*2][2] == 0){
          tab[val*2][0] =  tab[val][0] + 1;
          tab[val*2][1] = val;
          if( pthread_create(&t1, &attr, conject, (void *)(val*2)) != 0)
            fprintf(stderr, "Erreur dans un thread\n" );
        }
         
        if((val-1 %3) == 0 && tab[(val-1)/3][2] == 0){
          tab[(val-1)/3][0] =  tab[val][0] + 1;
          tab[(val-1)/3][1] = val;
          if( pthread_create(&t2, &attr, conject, (void *)((val-1)/3)) != 0)
            fprintf(stderr, "Erreur dans un thread\n" );
        }

        if(tab[val+1][2] == 0){
          tab[val+1][0] = conjectrec(val+1, 0);
          if(val%2==0)
            tab[val][1] = val/2;
          else
            tab[val][1] = val*3 +1;
          if( pthread_create(&t3, &attr, conject, (void *)(val+1)) != 0)
            fprintf(stderr, "Erreur dans un thread\n" );
        }
        printf("nb etape : %ld.  %ld -> %ld   |  %ld\n",tab[val][0], val, tab[val][1], tab[val][2]);
      }
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);


}