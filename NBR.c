#include <stdio.h>
#include <stdlib.h>

int secv_validation(int a, int b)//Aceasta fyunctie va valida daca cele 2 numere fac parte dintr-o secventa, adica daca a <= b, deoarece asta inseamna secventa
{
  if(b >= a){
    return 1;
  }
  return 0;
}

int read_elem(int *positions, ssize_t nr_elem)//vom citi numerele
{
  int a = 0;
  int b = 0;
  ssize_t length_secv = 1;
  int valid = 1;
  if(scanf("%d", &a) != 1)//avem deja un numar citit
    return -1;
  
  for(ssize_t i = 0;i < nr_elem;i++){//In timpul citirii numerelor vom determina dimensiunea secventei si aceea o vom salva in tablou, nu numerele.Functia returneaza 1 la succes si -1 la esec
    valid = 1;
    length_secv = 1;
    do{
      positions[i++] = length_secv++;
      valid = (i < nr_elem);
      if(valid){
	if(scanf("%d", &b) != 1)
	  return -1;
	valid = valid && secv_validation(a, b);
	a = b;
      }
    }while(valid);
    i--;
  }
  return 1;
}

void get_max_sizes(int *positions, ssize_t *sizes, ssize_t nr_elem)
{
  ssize_t max_size_right = 1;
  ssize_t size_secv = 1;
  for(ssize_t i = nr_elem - 1;i > 0;i--){
    if(i == nr_elem - 1){
      sizes[i] = 1;
    }
    if(positions[i] == 1){
      size_secv = 1;
    }
    else{
      size_secv++;
    }
    max_size_right = ((max_size_right > size_secv) ? (max_size_right) : (size_secv));
    if(positions[i] > 1){
      sizes[i - 1] = ((sizes[i] < max_size_right) ? (sizes[i] + 1) : (sizes[i]));
    }
    else{
      sizes[i - 1] = sizes[i];
    }
  }
}

int main(void)
{
  ssize_t nr_elem = 0;
  ssize_t K = 0;
  int positions[100];
  ssize_t sizes[100];
  ssize_t interogari = 0;
  scanf("%ld", &nr_elem);
  
  if(read_elem(positions, nr_elem) == -1){
    printf("Eroare la citire\n");
  }
  else{
    get_max_sizes(positions, sizes, nr_elem);

    if(scanf("%d", &interogari) != 1){
      printf("Prea putine numere introduse");
      exit(-1);
    }
  
    while(interogari--){
      if(scanf("%ld", &K) != 1){
	printf("Prea putine numere");
	exit(-1);
      }
      printf("%ld\n", sizes[K + 1]);
    }
  }
  return 0;
}
