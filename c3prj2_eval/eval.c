#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Helper function for qsort
//Multiplies *-1 because qsort sorts in ascending order
//and we want descending order
int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;

  int diff = (**cp1).value - (**cp2).value;

  if(diff == 0){
    diff = (**cp1).suit - (**cp2).suit;
  }

  diff*=-1;
  return diff;
}

//determines flushes
suit_t flush_suit(deck_t * hand) {
  size_t handSize = hand->n_cards;
  card_t ** card_arr = hand->cards;

  int suits[4] = {0};

  for(int i = 0; i < handSize; i++){
    suit_t a = card_arr[i]->suit;
      switch(a){
        case SPADES:
          suits[0]++;
	  if(suits[0] >= 5) {return SPADES;}
          break;	
	case HEARTS:
          suits[1]++;
       	  if(suits[1] >= 5) {return HEARTS;}
          break;	
	case DIAMONDS:
          suits[2]++;
	  if(suits[2] >= 5) {return DIAMONDS;}
          break;	
	case CLUBS:
          suits[3]++;
	  if(suits[3] >= 5) {return CLUBS;}
          break;       
        default:
	  break;
      }
  }
  
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned largest = 0;

  for(int i = 0; i < n; i++){
    if(arr[i] >= largest){
      largest = arr[i];
    }
  }

  return largest;
}

//returns the lowest index (match_counts) whose value is the n_of_akind,
//to find this groupe in the hand later
size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for(size_t i = 0; i < n; i++){
    if(match_counts[i] == n_of_akind){
      return i;
    }
    
  }

  printf("ERROR, %u should be in match_counts\n", n_of_akind);
  exit(EXIT_FAILURE);
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {

  size_t n = hand->n_cards;
  card_t ** arr = hand->cards;

  unsigned match_value = arr[match_idx]->value;
  
  for(ssize_t i = 0; i < n; i++){
    if(match_counts[i] > 1){
      if(arr[i]->value != match_value){
	return i;
      }
    }
  }

  return -1;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n);
  int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs);

  suit_t index_suit = hand->cards[index]->suit;

  //If fs!=NUM_SUITS, we look for a straight flush
  //But if index_suit is not fs, no straight flush 
  if(fs != NUM_SUITS){
    if(index_suit != fs){
      return 0;
    }
  }
  
  if(is_ace_low_straight_at(hand,index,fs)){
    return -1;
  } else{
    return is_n_length_straight_at(hand,index,fs,5);
  }
   
  return 0;
}

int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n){
  size_t handSize = hand->n_cards;
  card_t ** arr = hand->cards;

  //Target the value of the consecutive card (one less than index)
  unsigned target_value = (arr[index]->value) -1;
  
  n--; //We want to find n consecutive cards, excluding index

  for(size_t i = index +1; i < handSize; i++){
    //Check if the card is consecutive in value 
    if(arr[i]->value == target_value){

      //If searching straight flush, ignore if it's not the correct suit
      if(fs != NUM_SUITS){
	if(arr[i]->suit != fs){
	  continue;
	}
      }

      //Update target value and remaining consecutive cards "n" 
      target_value = (arr[i]->value) -1;
      n--;

      //If we didn't find a consecutive, there is no straight
    } else if(arr[i]->value < target_value){
      return 0;
    }

    //If we already counted n consecutives, n=0 and return
    if(!n){
      return 1;
    }
    
  }

  //If we did't find n consecutives, there's no straight
  return 0;
  
}

int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs){
  size_t handSize = hand->n_cards;
  card_t ** arr = hand->cards;

  if(arr[index]->value != VALUE_ACE){
    return 0;
  } else {
    for(size_t i = index + 1; i < handSize; i++){
      if(arr[i]->value == 5){

	//If searching straight flush, ignore if it's not the correct suit
	if(fs != NUM_SUITS){
	  if(arr[i]->suit != fs){
	    continue;
	  }
	}
	
	return is_n_length_straight_at(hand,i,fs,4);
	
      } else if(arr[i]->value < 5){
	return 0;
      }
      
    }
  }

  return 0;

}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  
  assert(n != 1);

  card_t ** arr = hand->cards;
  size_t handSize = hand->n_cards;

  hand_eval_t ans;
  ans.ranking = what;
  if(!idx){
    for(int i = 0; i < 5; i++){
      ans.cards[i] = arr[i];
    }
    
  } else {
    for(int i = 0; i < n; i++){
      ans.cards[i] = arr[idx+i];
    }

    //remaining empty cards in ans.cards
    unsigned rem = 5-n;

    for(int i = 0; i < idx; i++){

      if(rem){
	ans.cards[i+n] = arr[i];
	rem--;
      } else {
	break;
      }

    }

    for(int i = idx + n; i < handSize; i++){
    
      if(rem){
	ans.cards[i] = arr[i];
	rem--;
      } else {
	break;
      }
    
    }
  
  }

  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(hand2->cards[0]), card_ptr_comp);

  hand_eval_t hand_eval1 = evaluate_hand(hand1);
  hand_eval_t hand_eval2 = evaluate_hand(hand2);

  if(hand_eval1.ranking != hand_eval2.ranking){
    return hand_eval2.ranking - hand_eval1.ranking;
  } else {
    for(int i = 0; i < 5; i++){
      if(hand_eval1.cards[i]->value != hand_eval2.cards[i]->value){
	return hand_eval1.cards[i]->value - hand_eval2.cards[i]->value;
      }
    }

  }
  
  return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.

//allocates array of unsigned ints with as many elements
//as there are cards in the hand: basically, how many times
//a card of the same value appears in the hand
unsigned * get_match_counts(deck_t * hand){
  unsigned * match_counts = malloc((hand->n_cards)*sizeof(unsigned));

  for(size_t i = 0; i < hand->n_cards; i++){
    match_counts[i] = 1;
  }

  int j = 0;
  
  for(size_t i = 0; i < (hand->n_cards - 1); i++){
    if(hand->cards[i]->value == hand->cards[i+1]->value){
      j++; 
    } else {
      if(j != 0){
	for(int k = 0; k <= j; k++){
	  match_counts[i - k] += j;
	}
	j = 0;
      }
    }
  }

  if(j != 0){
    for(int k = 0; k <= j; k++){
      match_counts[hand->n_cards -1 - k] += j;
    }
    j = 0;
  }
  
  return match_counts;
  
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
