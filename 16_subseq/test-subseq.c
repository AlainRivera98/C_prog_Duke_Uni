#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void){

  int array0[] = {1};
  int array1[] = {5,0,1,2,3};
  int array2[] = {-10,-9,-8,-7,0,-5,2,3,4};
  int array3[] = {1,1,2,3};
  
  if(maxSeq(array0,(sizeof(array0)/sizeof(array0[0]))) != 1){printf("fail_0\n"); return EXIT_FAILURE;}
  if(maxSeq(array1,(sizeof(array1)/sizeof(array1[0]))) != 4){printf("fail_1\n"); return EXIT_FAILURE;}
  if(maxSeq(array2,(sizeof(array2)/sizeof(array2[0]))) != 5){printf("fail_2\n"); return EXIT_FAILURE;}
  if(maxSeq(array3,(sizeof(array3)/sizeof(array3[0]))) != 3){printf("fail_3\n"); return EXIT_FAILURE;}

  printf("No fail\n");
  
  return EXIT_SUCCESS;
}


