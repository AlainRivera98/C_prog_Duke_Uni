#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){

  size_t handSize = hand->n_cards;
  card_t ** card_arr = hand->cards; //array of pointers to card_t structs

  for(int i = 0; i < handSize; i++){
    print_card(*card_arr[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {

  assert_card_valid (c);
  int status = 0;
  size_t handSize = d->n_cards;
  card_t ** card_arr = d->cards;
  
  for(int i = 0; i < handSize; i++){
    assert_card_valid(*card_arr[i]);

    if((card_arr[i]->value == c.value) && (card_arr[i]->suit == c.suit)){
      status = 1;
    }
    
  }
  
  return status;
}

void shuffle(deck_t * d){
  size_t deckSize = d->n_cards;
  card_t ** card_arr = d->cards;
  card_t * temp;
 
    for(int i = 0; i < deckSize; i++){
      int j = rand()%deckSize;
      temp = card_arr[i];
      card_arr[i] = card_arr[j];
      card_arr[j] = temp;
      
    }  
  
}

void assert_full_deck(deck_t * d) {
  size_t deckSize = d->n_cards;
  
  assert(deckSize == 52);
  
  for(unsigned i = 0; i < deckSize; i++){
    card_t temp = card_from_num(i);
    assert(deck_contains(d,temp));

  }
  
}
