#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned ans){
  if(power(x,y) != ans){
    printf("Case %u^%u = %u detected as wrong\n\n",x,y,ans);
    exit(EXIT_FAILURE);
  }
}

int main(void){
  run_check(2,3,8);
  run_check(0,0,1);
  run_check(2000,2,4000000);
  run_check(0,100000,0);
  // if(power(-2,2) == 4){return EXIT_FAILURE;}
  //if(power(-1,2) == 1){return EXIT_FAILURE;}
  //run_check(2,20,1048576);

  

  return EXIT_SUCCESS;
}
