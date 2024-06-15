#include <stdio.h>
#include <stdbool.h>

bool succesor(int *aranjament, int poz, int n)
{
  if(aranjament[poz - 1] < n){
    aranjament[poz - 1]++;
    return true;
  }
  return false;
}

bool exist(int *aranjament, int poz)
{
  for(int i = 0;i < poz - 1;i++){
    if(aranjament[i] == aranjament[poz - 1]){
      return true;
    }
  }
  return false;
}

void show_arj(int *aranjament, int *multime, int k)
{
  for(int i = 0;i < k;i++){
    printf("%d ", multime[aranjament[i] - 1]);
  }
  printf("\n");
}

void generate(int *multime, int n, int k)
{
  int aranjament[100];
  bool succ = false;
  bool valid = false;
  int poz = 1;
  aranjament[0] = 0;
  while(poz > 0){
    succ = false;
    valid = false;
    if(poz <= k){
      do{
	succ = succesor(aranjament, poz, n);
	//printf("elem : %d poz : %d\n", aranjament[poz - 1], poz - 1);
	if(succ){
	  valid = exist(aranjament, poz);
	}
      }while(succ && valid);
    }
    if(succ){
      if(poz == k){
	show_arj(aranjament, multime, k);
      }
      else{
	aranjament[poz] = 0;
	poz++;
      }
    }
    else{
      poz--;
      aranjament[poz] = 0;
    }
  }
}

int main(void)
{
  int n = 0, k = 0, multime[100];
  scanf("%d", &n);
  scanf("%d", &k);
  if(k > n || n > 100){
    printf("Imposibil");
  }
  else{
    for(int i = 0;i < n;i++){
      scanf("%d", &multime[i]);
    }
    printf("Aranjamente de %d luate cate %d:\n", n, k);
    generate(multime, n, k);
  }
  return 0;
}
