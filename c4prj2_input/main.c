#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

deck_t * build_hand(){
  deck_t * deck = emptyDeck();

  for(unsigned i = 0; i < 52; i++){
    card_t card = card_from_num(i);
    add_card_to(deck, card);
  }

  shuffle(deck);

  deck_t * hand = emptyDeck();

  for(size_t i = 0; i < 13; i++){
    card_t *c = deck->cards[i];
    add_card_to(hand, *c);
  }

  free_deck(deck);

  return hand;

}


int main(int argc, char ** argv){

  if(argc != 2){
    char *err_str;
    err_str = (argc > 2)?"More arguments than needed\n":"No file: need arguments\n";
    fprintf(stderr,"%s",err_str);
    return EXIT_FAILURE;
  }

  FILE *f = fopen(argv[1],"r");

  size_t n_hands = 0;
  future_cards_t * fc = empty_future();
  
  deck_t ** handArray = read_input(f, &n_hands, fc);
 
  deck_t * unknown_hand = build_hand();
  
  future_cards_from_deck(unknown_hand, fc);

  for(size_t i = 0; i < n_hands; i++){
    print_hand(handArray[i]);
    printf("\n");
    free_deck(handArray[i]);
  }
  printf("\nUnknown hand:\n");
  print_hand(unknown_hand);
  printf("\n\n");
  
  free(handArray);
  
  if(fclose(f) != 0){
    perror("Failed to close the file!\n");
    return EXIT_FAILURE;
  }

  free_future(fc);
  free_deck(unknown_hand);
  
  return(EXIT_SUCCESS);
}
