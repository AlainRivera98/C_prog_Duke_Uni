#include <stdio.h>
#include <stdlib.h>

unsigned power_helper(unsigned x, unsigned y, unsigned z){

  if(x == 0){
    unsigned ans = (y == 0) ? 1 : 0;
    return ans;
  } else if (y == 0){
    return 1;
  } else if (y == 1){
    return x*z;
  } else {
    return power_helper(x,y-1,x*z);
  }

}

unsigned power(unsigned x,unsigned y){
  return power_helper(x,y,1);
}
