#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double printRetire(int age, double amount, retire_info current){

  for(int i = 1; i <= current.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n", age/12, age%12, amount);
    age++;
    amount = amount*(1 + current.rate_of_return) + current.contribution;  
    
  }

  return amount;
  
}


void retirement(int startAge,         //in months
		double initial,       //initial savings in dollars
		retire_info working,  //info about working
		retire_info retired){ //info about being retired

  double amount = 0;
  
  amount = printRetire(startAge, initial, working);
  amount = printRetire(startAge+working.months, amount, retired);
}


int main(void){

  retire_info working;
  retire_info retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  //Starting conditions: 327 months, 21345 savings
  retirement(327,21345,working,retired);
  
  return EXIT_SUCCESS;
}
