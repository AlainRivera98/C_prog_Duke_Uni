#include "cards.h"
#include <stdio.h>
#include <stdlib.h>
int main(void) {

  printf("\n");
  
  card_t try;
  try = card_from_letters('2','c');
  print_card(try);
  printf("\n");
  
  try = card_from_num(0);
  print_card(try);

  hand_ranking_t rank = TWO_PAIR;
  printf("\n%s",ranking_to_string(rank));
  
  printf("\n\n");
  
  return 0;
}
