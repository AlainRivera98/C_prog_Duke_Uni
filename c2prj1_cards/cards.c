#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value>=2 && c.value<=VALUE_ACE);
  assert(c.suit>=SPADES && c.suit<=CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){  
    case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH\n"; break;
    case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND\n"; break;
    case FULL_HOUSE: return "FULL_HOUSE\n"; break;
    case FLUSH: return "FLUSH\n"; break;
    case STRAIGHT: return "STRAIGHT\n"; break;
    case THREE_OF_A_KIND: return "THREE_OF_A_KIND\n"; break;
    case TWO_PAIR: return "TWO_PAIR\n"; break;
    case PAIR: return "PAIR\n"; break;
    case NOTHING: return "NOTHING\n"; break;
    default: return "Invalid case\n"; break;
  }
  return "";
}

char value_letter(card_t c) {
  if(c.value>=2 && c.value<=9){
    return '0'+c.value;
  } else {
    switch(c.value){
      case 10: return '0'; break;
      case VALUE_JACK: return 'J'; break;
      case VALUE_QUEEN: return 'Q'; break;
      case VALUE_KING: return 'K'; break;
      case VALUE_ACE: return 'A'; break;
      default: return 'x'; break;
    }

  }
		 
  return 'x';
}


char suit_letter(card_t c) {
  switch(c.suit){
    case SPADES: return 's'; break;
    case HEARTS: return 'h'; break;
    case DIAMONDS: return 'd'; break;
    case CLUBS: return 'c'; break;
    case NUM_SUITS: return 'n'; break;
    default: return 'x'; break;
  }


  return 'x';
  
}

void print_card(card_t c) {
  assert_card_valid(c);
  printf("%c%c",value_letter(c),suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;

  if(value_let>='2' && value_let<='9'){
    temp.value = value_let - '0';
  } else {
    switch(value_let){
      case '0': temp.value = 10; break;
      case 'J': temp.value = VALUE_JACK; break;
      case 'Q': temp.value = VALUE_QUEEN; break;
      case 'K': temp.value = VALUE_KING; break;
      case 'A': temp.value = VALUE_ACE; break;
      default: temp.value = 100; break;
	
    }
    
  }

  switch(suit_let){
    case 's': temp.suit = SPADES; break;
    case 'h': temp.suit = HEARTS; break;
    case 'd': temp.suit = DIAMONDS; break;
    case 'c': temp.suit = CLUBS; break;
    default: temp.suit = NUM_SUITS; break;
  }
  
  assert_card_valid(temp);
  
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.value = (c%13)+2;
  temp.suit = c/13;
  temp = card_from_letters(value_letter(temp),suit_letter(temp));

  return temp;
}
