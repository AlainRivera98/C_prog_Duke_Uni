#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

void checkSpace(const char *c);
void deleteSpace(const char ** c);

//File has to be opened, but this function won't close it:
//both things must be done outside the function
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  deck_t ** handArray = malloc(sizeof(*handArray));

  if(f == NULL){
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  deck_t * deck;

  char * line = NULL;
  size_t sz;

  *n_hands = 0;

  while(getline(&line, &sz, f) >= 0){
    deck = hand_from_string(line, fc);
    handArray = realloc(handArray,(*n_hands + 1)*sizeof(*handArray));
    handArray[*n_hands] = deck;
    (*n_hands)++;
  }

  free(line);

  return handArray;
}

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  deck_t * deck = emptyDeck();

  const char * c = str;
  int cardCount = 0;

  while((*c) != '\0'){
    
    deleteSpace(&c);
    
    if(strlen(c) >= 3){
      //Checks normal cards
      if((*c) != '?'){
       	card_t card = card_from_letters(*c,*(c+1));
	add_card_to(deck, card);
	
	c+=2;
	checkSpace(c);
	c++;
      } else {
	c++;
	//checks unknown cards
	//they start with a '?'
	if(isdigit(*c)){
	  if(isdigit(*(c+1))){
	    char num[3];
	    num[0] = c[0];
	    num[1] = c[1];
	    num[2] = '\0';
	  
	    size_t index = atoi(num);
	    if(index > 52){
	      perror("Unknown card number bigger than deck\n");
	      exit(EXIT_FAILURE);
	    }
	    card_t * emptyCard = add_empty_card(deck);
	    add_future_card(fc,index,emptyCard);

	    c+=2;
	  } else if((*(c+1) == ' ') || (*(c+1) == '\n')){
	    char num[2]; 
	    num[0] = c[0];
	    num[1] = '\0';

	    size_t index = atoi(num);
	    card_t * emptyCard = add_empty_card(deck);
	    add_future_card(fc,index,emptyCard);

	    c++;
	  } else {
	    perror("Incorrect format. Check string");
	    exit(EXIT_FAILURE);
	  }
	  
	} else {
	  perror("Incorrect format. Should be a number\n");
	  exit(EXIT_FAILURE);
	}
	
	checkSpace(c);
	c++;
      }
      
    } else {
      deleteSpace(&c);
      if((*c) == '\n'){
	c++;
      } else {
	printf("Jeje, aqui ta el error:%s%s%s\n","...",c,"...");
	perror("String is on wrong format. Perhaps too short\n");
	exit(EXIT_FAILURE);
      }
    }

    cardCount++;
  }

  if(cardCount < 5){
    perror("Error: hand should have at least 5 cards\n");
    exit(EXIT_FAILURE);
  }
  
  return deck;

}

void checkSpace(const char *c){
  if((*c) != ' ' && (*c) != '\n'){
    perror("No space where it should be\n");
    exit(EXIT_FAILURE);
  } else if ((*c) == '\n'){
    if((*(c+1)) != '\0'){
      perror("No end of string where it should be\n");
      exit(EXIT_FAILURE);
    }
  }
  
}

//Deletes trailing spaces
void deleteSpace(const char ** c){
  while((**c) == ' '){
    (*c)++;
  }
}
