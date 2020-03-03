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
//int valfin = 2147483647;

int conject(int val, int etape){
  if(val%2==0)
    tab[val][1] = val/2;
  else
    tab[val][1] = 3*val +1;
  tab[val][0] = etape;
  printf("%ld. %d\n",tab[val][0], val);
  if(val==1)
    return 1;
  conject(tab[val][1], etape+1);
}

int main(int argc, char *argv[]){

  int valdebut = atoi(argv[1]);

  if(valdebut > 0 && argc > 1){
    conject(valdebut, 1);
  }

  return 0;
}
