#include <stdio.h>
#include <stdlib.h>
int* myarray(size_t n)
{
  int i;
  int* p;
  p = malloc(n*sizeof(*p));
  printf("pointer to array is: %p\n", p);
  
  for(i=0;i<n;i++)
    p[i]=i+250;
  
  return p;
}

int main()
{
  int* ptrToArray = myarray(3);
  printf("pointer to array is: %p\n", ptrToArray);
  printf("value of  array is: %d\n", *ptrToArray);
  printf("value of  array is: %d\n", *ptrToArray+1);
  printf("value of  array is: %d\n", *ptrToArray+2);
  free(ptrToArray);
}

