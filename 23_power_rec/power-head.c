#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x,unsigned y){

  if(x == 0){
    unsigned ans = (y == 0) ? 1 : 0;
    return ans;
  } else if (y == 0){
    return 1;
  } else if (y == 1){
    return x;
  } else {
    return x*power(x,y-1);
  }
  
}
