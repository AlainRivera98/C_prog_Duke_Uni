#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"

deck_t * emptyDeck(void){
  deck_t * emptyDeck = malloc(sizeof(deck_t));
  emptyDeck->n_cards = 0;
  emptyDeck->cards = malloc(sizeof(*emptyDeck->cards));

  return emptyDeck;
}

deck_t *  build_deck(void){
  deck_t * d = emptyDeck();
  
  for(unsigned i = 0; i < 52; i++){
    card_t c = card_from_num(i);
    add_card_to(d, c);
  }

  print_hand(d);

  return d;
}

int main(void){
  deck_t *deck = build_deck();

  shuffle(deck);

  print_hand(deck);
  printf("\n");

  deck_t * hand = emptyDeck();
  deck_t * hand2 = emptyDeck();

  for(size_t i = 0; i < 5; i++){
    card_t * c = deck->cards[i];
    add_card_to(hand, *c);
    c = deck->cards[i+5];
    add_card_to(hand2, *c);
    
  }

  size_t n_hands = 2;
  deck_t * hands[] = {hand, hand2};

  deck_t * rem_deck = build_remaining_deck(hands,n_hands);
  
  printf("\n");
  print_hand(hands[0]);
  printf("\n");

  printf("\n");
  print_hand(hands[1]);
  printf("\n");

  printf("\n");
  print_hand(rem_deck);
  printf("\n");
  
  free_deck(hand);
  free_deck(hand2);
  free_deck(deck);
  free_deck(rem_deck);
  
  return EXIT_SUCCESS;
}
