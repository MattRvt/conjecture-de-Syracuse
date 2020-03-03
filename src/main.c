/**
 * - amélioration espéré: faire marcher le programme pour 1,2,4,8,16,3,-1
 * - amélioration effective:
 * - temps d'exécution pour 77777: 
 *
 *  
*/

#include <stdio.h>


long int tab[3000][1];
int valfin = 50;

int conject(int val){
  if(val%2==0)
    tab[val][1] = val/2;
  else
    tab[val][1] = 3*val +1;

  if(val>valfin)
    return 0;
  conject(val+1);
}

int main(int argc, char *argv[]){
  if(argv[1] > 0){
    conject(argv[1]);
  }

  return 0;
}
