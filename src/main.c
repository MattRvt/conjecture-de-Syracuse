#include <stdio.h>
#include <time.h>

long int tab[3000][1];
int valfin = 50;


int conject(int val){
  if(val%2==0)
    tab[val][1] = val/2;
  else
    tab[val][1] = 3*val +1;
  printf("%d : %d\n", val, tab[val][1]);
  if(val>valfin)
    return 0;
  conject(val+1);
}

int main(){

  conject(8);

  return 0;
}
