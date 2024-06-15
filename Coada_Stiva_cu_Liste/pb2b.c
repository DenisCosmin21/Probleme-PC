#include <stdio.h>
#include <stdbool.h>

int main(void)
{
  FILE *input = fopen("data.in", "r");
  FILE *output = fopen("data.out", "w");
  
  size_t candidati = 0;
  size_t nr_doleante = 0;
  int doleante[100];
  int frecventa_optiuni[100];
  bool new_option = false;
  size_t result = 0;
  int doleanta = 0;
  int optiune_candidat = 0;
  size_t optiuni_candidat;
  
  for(size_t i = 0;i < 100;i++){
    frecventa_optiuni[i] = 0;//initializam frecdventa
    doleante[i] = 0;
  }
  
  fscanf(input, "%ld", &nr_doleante);

  for(size_t i = 0;i < nr_doleante;i++){
    fscanf(input, "%d", &doleanta);
    doleante[doleanta - 1] = 1;//setam una din doleante pe 1 in cauzl in care exista, dsca nu va ramane 0. facem asta pentru o cautare mai usoara a doleantelor
  }

  fscanf(input, "%ld", &candidati);

  for(size_t i = 0;i < candidati;i++){
    new_option = false;
    fscanf(input, "%ld", &optiuni_candidat);
    for(size_t j = 0;j < optiuni_candidat;j++){
      fscanf(input, "%d", &optiune_candidat);
      if(doleante[optiune_candidat - 1] == 1){
	if(frecventa_optiuni[optiune_candidat - 1] == 0){
	  frecventa_optiuni[optiune_candidat-1] = 1;
	  new_option = true;
	}
      }
    }
    if(new_option == true){
      result++;
    }
  }

  printf("%ld", result);

  fclose(input);
  fclose(output);
  return 0;
}
  
