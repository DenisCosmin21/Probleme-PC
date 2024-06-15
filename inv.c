#include <stdio.h>

#define modulus 9917

size_t mergeSort(size_t left, size_t right, long long *A) {
  size_t mij = (left + right) / 2, dim = 0;
  long long B[100001];
  size_t rez = 0;
    size_t i = left, j = mij + 1;
    while (i <= mij && j <= right) {
        if (A[i] > A[j]) {
	  dim++;
          B[dim] = A[j];
          rez +=( mij - i + 1)%modulus;
           j++;
        }
	else {
           dim++;
           B[dim] = A[i];
           i++;
        }
    }
    while (i <= mij) {
        dim++;
        B[dim] = A[i];
        i++;
    }
    while (j <= right) {
        dim++;
        B[dim] = A[j];
        j++;
    }
    dim = 0;
    for (i = left; i <= right; i++) {
        dim++;
        A[i] = B[dim];
    }
    return rez;
}

size_t divide_impera(size_t left, size_t right, long long *A) {
    if (left < right) { // Verificați dacă există cel puțin două elemente în subșir
        size_t mij = (left + right) / 2;
        return divide_impera(left, mij, A) + divide_impera(mij + 1, right, A) + mergeSort(left, right, A);
    }
    return 0;
}

int main()
{
  size_t n;
  long long A[100001];
  FILE *input = fopen("inv.in", "r");
  FILE *output = fopen("inv.out", "w");

  fscanf(input, "%ld", &n);

  for(size_t i = 1;i <= n;i++){
    fscanf(input, "%lld", &A[i]);
  }

  fprintf(output, "%ld", divide_impera(1, n, A) % modulus);

  fclose(input);
  fclose(output);

  return 0;
}

