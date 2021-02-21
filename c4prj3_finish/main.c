#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void monteCarlo(unsigned * wins, size_t n_hands, unsigned num_trials,
		deck_t * remainDeck, future_cards_t * fc, deck_t ** handArray);


int main(int argc, char ** argv) {
  unsigned num_trials = 10000;
  
  //Check if given number of num_trials
  if(argc == 3){
    int num = atoi(argv[2]);
    if(num <= 0){
      perror("Argument for num_trials is invalid\n");
      return EXIT_FAILURE;
    }
    
    num_trials = num;
  } else if(argc != 2){
    char *err_str;
    err_str = (argc > 2)?"More arguments than needed\n":"No file: need arguments\n";
    fprintf(stderr,"%s",err_str);
    return EXIT_FAILURE;
  }

  FILE *f = fopen(argv[1], "r");

  size_t n_hands = 0;
  future_cards_t * fc = empty_future();
  deck_t ** handArray = read_input(f, &n_hands, fc);
  deck_t * remainDeck = build_remaining_deck(handArray, n_hands);

  //array for wins/tie counts
  unsigned * wins = malloc((n_hands + 1)*sizeof(size_t));

  for(size_t i = 0; i <= n_hands; i++){
    wins[i] = 0;
  }

  //Compute Monte Carlo simulation
  monteCarlo(wins, n_hands, num_trials, remainDeck, fc, handArray);

  //print results and free array of hands
  for(size_t i = 0; i < n_hands; i++){
    printf("Hand %zu won %u / %u times (%.2f%%)\n",
	   i, wins[i], num_trials, (100.0*wins[i]/(double)num_trials)); 
    free_deck(handArray[i]);
  }

  printf("And there were %u ties\n", wins[n_hands]);

  if(fclose(f) != 0){
    perror("Faled to close the file!\n");
    return EXIT_FAILURE;
  }

  //free remaining allocated dynamic memory
  free(wins);
  free_deck(remainDeck);
  free(handArray);
  free_future(fc);
  
  return EXIT_SUCCESS;
}

//Computes Monte Carlo simulation: shuffles and assigns unknown cards,
//compares all hands, check for wins and ties, and does it num_trials times.
void monteCarlo(unsigned * wins, size_t n_hands, unsigned num_trials,
		deck_t * remainDeck, future_cards_t * fc, deck_t ** handArray){

  for(size_t i = 0; i < num_trials; i++){
    shuffle(remainDeck);
    future_cards_from_deck(remainDeck, fc);

    size_t winner = 0;
    int tie = 0;

    for(size_t j = 1; j < n_hands; j++){
      int compare = compare_hands(handArray[winner],handArray[j]);

      //compare_hands returns > 0 if first hand is better,
      // < 0 if second hand is better,
      // and 0 if they are equal
      if(compare < 0){
	winner = j;
	tie = 0;
      } else if (compare == 0){
	tie = 1;
      }      
    }
    
    if(tie){
      wins[n_hands]++; //Count tie
    } else {
      wins[winner]++; //Count winner
    }
  }
}
