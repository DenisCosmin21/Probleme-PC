#include <stdio.h>
#include <stdlib.h>

typedef struct{
  long long val;
  size_t poz;
}node_info;

size_t mergeSort(int left,int right, node_info *B)
{
    node_info C[100001];
    size_t rez = 0;
    size_t i=left, mij = (left+right)/2, j=mij+1, size=0;
    while(i<=mij && j<=right)
    {
        if(B[i].poz<B[j].poz)
        {
            C[size++] = B[i++];
        }
        else
        {
            rez +=(mij-i+1);
            C[size++] = B[j++];
        }
    }
    if(i<=mij)
    {
        while(i<=mij)
        {
            C[size++]=B[i++];
        }
    }
    else
        while(j<=right)
        {
            C[size++] = B[j++];
        }
    size=0;
    for(i=left;i<=right;i++)
    {
        B[i] = C[size++];
    }
    return rez;
}

size_t divide(size_t left, size_t right, node_info *B)
{
    if(left<right)
    {
      
      size_t mij=(left + right)/2;
	
      return divide(left,right, B) + divide(mij+1,right, B) +  mergeSort(left,right, B);
    }

    return 0;
}

int main()
{
  FILE *input = fopen("inv.in", "r");
  FILE *output = fopen("permutariab.out", "w");
  
  size_t n = 0;
  
  long long parcurs[100001], A[100001];
  long long x = 0;
  
  node_info B[100001];
  
  fscanf(input, "%ld", &n);
  /*for(size_t i=1;i<=n;i++)
    {
      fscanf(input, "%lld", &x);
      B[x].val = i;
    }
    for(size_t i=1;i<=n;i++)
    {
      fscanf(input, "%lld", &x);
      B[i].poz = B[x].val;

    }
    printf("%ld", divide(1,n, B));
  */
  // fclose(input);
    fclose(output);
    return 0;
}
