#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  //Initialize counts_t c and its elements
  counts_t * c = malloc(sizeof(counts_t));
  c->array = NULL;
  c->n = 0;
  c->unknown_count = 0;

  return c;
}

void addCount(counts_t * c, const char * name) {
  if(name != NULL){
    for(size_t i = 0; i < c->n; i++){
      if(strcmp(name,c->array[i]->value) == 0){
	c->array[i]->count++;
	return;
      }
    }

    //If new name/value
    //*c->array = *one_count_t
    c->array = realloc(c->array,(c->n + 1)*sizeof(*c->array));

    c->array[c->n] = malloc(sizeof(one_count_t));
    c->array[c->n]->value = malloc((strlen(name) + 1)*sizeof(char));
    strncpy(c->array[c->n]->value,name, strlen(name) + 1);
    c->array[c->n]->count = 1;

    c->n++;
    
  } else {
    c->unknown_count++;
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  if(outFile == NULL){
    perror("Problem with outfile");
    exit(EXIT_FAILURE);
  }

  for(size_t i = 0; i < c->n; i++){
    fprintf(outFile, "%s: %lu\n", c->array[i]->value, c->array[i]->count);
  }

  if(c->unknown_count){
    fprintf(outFile, "<unknown> : %lu\n", c->unknown_count);
  }
}

void freeCounts(counts_t * c) {
  for(size_t i = 0; i < c->n; i++){
    free(c->array[i]->value);
    free(c->array[i]);
  }

  free(c->array);
  free(c);
}
