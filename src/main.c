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
#include <pthread.h>
#define MAX 10000000

long int tab[MAX][1];
clock_t begin;
//int valfin = 2147483647;
void *wrtiteData_thread(void *arg);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int conject(long int val, int etape)
{
  if (val % 2 == 0)
    tab[val][1] = val / 2;
  else
    tab[val][1] = 3 * val + 1;
  if (val == 1)
    tab[val][0] = 0;
  else
    tab[val][0] = conject(tab[val][1], etape + 1) + 1;
  //printf("%ld. %ld\n", tab[val][0], val);
  pthread_t thr;
  if (pthread_create(&thr, NULL, wrtiteData_thread, (void *)val) != 0)
  {
    fprintf(stderr, "Erreur dans pthread_create\n");
    exit(EXIT_FAILURE);
  }

  return tab[val][0];
}

int main(int argc, char *argv[])
{
  for (int i = 1; i < 250; i++)
  {
    printf("i= %d \n", i);
    begin = clock();
    conject(i, 1);
  }

  return 0;
}

void *wrtiteData_thread(void *arg)
{
  long int val = (long int)arg;
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  pthread_mutex_lock(&mutex);
  //printf("run time: %f \n", time_spent);

  FILE *pFile;

  pFile = fopen("data.txt", "a");
  if (pFile == NULL)
  {
    perror("Error opening file.");
  }
  else
  {
    //ecrire val dans le fichier
    fprintf(pFile, "%ld", val);
    //tabulation
    fprintf(pFile, "%s", " ");
    //ecrire temps dans le fichier
    fprintf(pFile, "%f", time_spent);
    //nouvelle ligne
    fprintf(pFile, "%s", "\n");
  }
  fclose(pFile);
  pthread_mutex_unlock(&mutex);
  pthread_exit(0);
}
