#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void){

  int array0[] = {1};
  int array1[] = {5,0,1,2,3};
  int array2[0];
  int array3[] = {-10,-9,-8,-7,0,-5,2,3,4};
  int array4[] = {1,1,2,3};
  //int array6[] = {2,4,6,8,0,1,10,99,124};
  //int array5[] = {1,2,3,0,1,2};
  
  if(maxSeq(array0,(sizeof(array0)/sizeof(array0[0]))) != 1){return EXIT_FAILURE;}
  if(maxSeq(array1,(sizeof(array1)/sizeof(array1[0]))) != 4){return EXIT_FAILURE;}
  if(maxSeq(array2,0) != 0){return EXIT_FAILURE;}
  if(maxSeq(array3,(sizeof(array3)/sizeof(array3[0]))) != 5){return EXIT_FAILURE;}
  if(maxSeq(array4,(sizeof(array4)/sizeof(array4[0]))) != 3){return EXIT_FAILURE;}
  //if(maxSeq(array5,(sizeof(array5)/sizeof(array5[0]))) != 3){return EXIT_FAILURE;}
  //if(maxSeq(array6,(sizeof(array6)/sizeof(array6[0]))) != 5){return EXIT_FAILURE;}
  
  
  return EXIT_SUCCESS;
}


