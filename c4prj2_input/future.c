#include <stdio.h>
#include <stdlib.h>
#include "future.h"

//add future cards to an INITIALIZED future_cards_t
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  if(index >= fc->n_decks){
    //*fc->decks == deck_t
    fc->decks = realloc(fc->decks, (index + 1)*sizeof(*fc->decks));
    for(size_t i = fc->n_decks; i <= index; i++){
      fc->decks[i].cards = NULL;
      fc->decks[i].n_cards = 0;
     
    }
    fc->n_decks = index + 1;
  }
  
  fc->decks[index].cards = realloc(fc->decks[index].cards,
    (fc->decks[index].n_cards + 1)*sizeof(card_t *));
  fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
  fc->decks[index].n_cards++;
  
}

//Fills future_cards_t fc with cards in deck
void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if(deck->n_cards < fc->n_decks){
    perror("Amount of cards in deck is less than in future cards\n");
    return;
  }
  
  //size_t k = 0;
  for(size_t i = 0; i < fc->n_decks; i++){
    card_t * c = deck->cards[i];
    deck_t * d = &(fc->decks[i]);
    
    if(d->n_cards == 0) {
      
      continue;
    }

    for(size_t j = 0; j < d->n_cards; j++){
      d->cards[j]->value = c->value;
      d->cards[j]->suit = c->suit;
    }
  }
  
}

future_cards_t * empty_future(void){
  future_cards_t * fc = malloc(sizeof(future_cards_t));
  fc->n_decks = 0;
  fc->decks = malloc(sizeof(*fc->decks));

  return fc;
}

void free_future(future_cards_t * fc){
  for(size_t i = 0; i < fc->n_decks; i++){
    if(fc->decks[i].n_cards != 0){
      free(fc->decks[i].cards);
    }
  }

  free(fc->decks);
  free(fc);
}
