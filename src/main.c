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

int main(){
  if(valfin > 0){
    conject(2);
  }

  return 0;
}
