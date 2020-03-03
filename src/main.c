/**
 * - amélioration espéré: faire marcher le programme pour 1,2,4,8,16,3,-1
 * - amélioration effective:
 * - temps d'exécution pour 77777:
 *
 *
*/

#include <stdio.h>
#include <time.h>

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

<<<<<<< HEAD
int main(){

  conject(58);
=======
int main(int argc, char *argv[]){
  if(argv[1] > 0){
    conject(argv[1]);
  }
>>>>>>> a7bc16bc23baf8d43bb02b3d1d35ac5496ae05ca

  return 0;
}
