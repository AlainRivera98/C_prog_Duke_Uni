#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){

  size_t maxSeq = 0;
  size_t tempSeq = 0;

  if(n > 0){
    tempSeq++;
    for(int i = 1; i < n; i++){
      if(array[i] > array[i-1]){
	tempSeq++;
      } else {
	if (tempSeq > maxSeq) {
	  maxSeq = tempSeq; 
	}
	
	tempSeq = 1;
      }
    }
    if (tempSeq > maxSeq){
      maxSeq = tempSeq;
    }
    
  }

  return maxSeq;

}
