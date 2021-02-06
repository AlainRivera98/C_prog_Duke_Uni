#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void add_card_to(deck_t * deck, card_t c){

  deck->cards = realloc(deck->cards,(deck->n_cards + 1)*sizeof(*deck->cards));
  deck->cards[deck->n_cards] = malloc(sizeof(card_t));
  
  deck->cards[deck->n_cards]->value = c.value;
  deck->cards[deck->n_cards]->suit = c.suit;

  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck){
  card_t * c = malloc(sizeof(card_t));
  c->value = 0;
  c->suit = 0;
  add_card_to(deck, *c);

  free(c);

  return deck->cards[deck->n_cards -1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t * exclusive_deck = malloc(sizeof(deck_t));
  exclusive_deck->n_cards = 0;
  exclusive_deck->cards = malloc(sizeof(*exclusive_deck->cards)); 
  
  for(unsigned i = 0; i < 52; i++){
    card_t c = card_from_num(i);
    if(!deck_contains(excluded_cards,c)){
      add_card_to(exclusive_deck,c);
    }
  }

  return exclusive_deck;
  
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  deck_t * excluded_cards = malloc(sizeof(deck_t));
  excluded_cards->n_cards = 0;
  excluded_cards->cards = malloc(sizeof(*excluded_cards->cards));
  
  for(size_t i = 0; i < n_hands; i++){
    deck_t * d = hands[i];
    //There was sigfault below for putting i instead of j in the loop
    for(size_t j = 0; j < d->n_cards; j++){
      card_t * c = d->cards[j];
      if(c->value >=2 && c->value <= VALUE_ACE && c->suit >= SPADES && c->suit <= CLUBS){
	add_card_to(excluded_cards, *c);
      }
    }
  }

  deck_t * remain_deck = make_deck_exclude(excluded_cards);
  free_deck(excluded_cards);

  return remain_deck;
  
}

void free_deck(deck_t * deck){
  for(size_t i = 0; i < deck->n_cards; i++){
    free(deck->cards[i]);
  }

  free(deck->cards);
  free(deck);
}

deck_t * emptyDeck(void){
  deck_t * emptyDeck = malloc(sizeof(deck_t));
  emptyDeck->n_cards = 0;
  emptyDeck->cards = malloc(sizeof(*emptyDeck->cards));

  return emptyDeck;
}

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
