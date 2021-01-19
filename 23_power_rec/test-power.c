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

  printf("13^2 = %u\n",power(13,2));
  printf("0^24 = %u\n",power(0,24));
  printf("1^20 = %u\n",power(1,20));
  printf("2^10 = %u\n",power(2,10));
  printf("Everything is fine!\n\n");

  return EXIT_SUCCESS;
}
