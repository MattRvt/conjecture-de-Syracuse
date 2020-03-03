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

long int tab[3000][1];
int valfin = 200;

int conject(int val){
  if(val%2==0)
    tab[val][1] = val/2;
  else
    tab[val][1] = 3*val +1;
  printf("%d\n", val);
  if(val>valfin || val==1)
    return 0;
  conject(tab[val][1]);
}

int main(int argc, char *argv[]){

  int valdebut = atoi(argv[1]);

  if(valdebut > 0 && argc > 1){
    conject(valdebut);
  }

  return 0;
}