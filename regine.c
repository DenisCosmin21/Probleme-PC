#include <stdio.h>
#include <stdbool.h>

bool succesor(int *elem, int n)
{
  if(*elem < n){
    *elem += 1;
    return true;
  }
  else{
    return false;
  }
}

bool validate_position(int *table_line, int poz, int n)
{
  for(int i = 0;i < poz - 1;i++){
    //printf("Line from %d : %d ; Last line from %d : %d ; diag_left %d : %d ; diag_right %d : %d \n", i, table_line[i], poz - 1, table_line[poz - 1], ((poz - 1) - i), table_line[poz - 1] - ((poz - 1) - i), ((poz - 1) + i), table_line[poz - 1] + ((poz - 1) - i));
    if(table_line[i] == table_line[poz - 1] - ((poz - 1) - i)){
      return false;
    }
    else if(table_line[i] == table_line[poz - 1] + ((poz - 1) - i)){
      return false;
    }
    else if(table_line[i] == table_line[poz - 1]){
      return false;
    }
  }
  return true;
}

void show_queen_table(int *table_line, int n)
{
  for(int i = 0;i < n;i++){
    printf("_");
    for(int j = 0;j < n;j++){
      printf("____");
    }
    printf("\n");
    for(int j = 0;j < n;j++){
      printf("|");
      if(j == table_line[i] - 1){
	printf(" Q ");
      }
      else{
	printf("   ");
      }
    }
    printf("|");
    printf("\n");
  }
  printf("_");
  for(int j = 0;j < n;j++){
      printf("____");
    }
  printf("\n");
}

void queen_arrange(int n)
{
  int cnt = 1;
  int table_line[13];
  int poz = 1;
  table_line[0] = 0;
  bool succ, valid;
  while(poz > 0){
    succ = false;
    valid = false;
    if(poz <= n){
      //printf("Iteration : %d\n", poz);
      do{
	succ = succesor(&table_line[poz - 1], n);
	//printf("Position %d : ", poz);
	//printf("Value : %d ; ", table_line[poz-1]);
	//printf("succesor: %d ; ", succ);
	if(succ){
	  valid = validate_position(table_line, poz, n);
	}
	//printf("Valid: %d\n", valid);
      }while(succ && !valid);
    }
    if(succ){
      if(poz == n){
	printf("\n");
	printf("Varianta de asezare a reginelor nr : %d\n", cnt++);
	show_queen_table(table_line, n);
      }
      else{
	table_line[poz] = 0;
	poz++;
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
  if(n < 4 || n > 13){
    printf("Imposibil");
  }
  else{
    printf("Se asaza damele pe tabla :\n");
    queen_arrange(n);
  }
  return 0;
}
