#include <stdio.h>
#include <stdbool.h>

void show_perm(int *permutare, int *multime, int n)
{
  for(int i = 0;i <= n;i++){
    printf("%d ", multime[permutare[i]]);
  }
  printf("\n");
}

bool exist(int *permutare, int poz)
{
  for(int i = 0;i < poz;i++){
    if(permutare[i] == permutare[poz]){
      return true;
    }
  }
  return false;
}

bool succesor(int *permutare, int poz, int n)
{
  if(permutare[poz] < n - 1){
    permutare[poz]++;
    return true;
  }
  else{
    return false;
  }
}

void generate_perm(int *multime, int n)
{
  int permutare[100];
  int poz = 0;
  bool succ = false;
  bool val = false;
  permutare[0] = -1;
  while(poz >= 0){
    succ = false;
    val = false;
    if(poz < n){
      do{	
        succ = succesor(permutare, poz, n);
	if(succ){
	  val = !exist(permutare, poz);
	}
      }while(succ && !val);
    }
      if(succ){
	if(poz == n - 1){
	  show_perm(permutare, multime, poz);
	}
	else{
	  poz++;
	  permutare[poz] = -1;
	}
      }
      else{
	poz--;
      }
  }
}
      
	
    
int main(void)
{
  int n = 0;
  scanf("%d", &n);
  int multime[100];
  if(n <= 100){
    //printf("%d\n", n);
    for(int i = 0;i < n;i++){
      scanf("%d", &multime[i]);
    }
    printf("Permutari de %d:\n", n);
    generate_perm(multime, n);
  }
  else{
    printf("Too many elements");
  }
  return 0;
}
  
