#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

//Fill key and value
/*For Key: malloc #chars between first char and '=', plus a '\0'
  then copy string before '=' and set '\0'
  For Value: same but between '=' and '\n'
  copy string after '=' and overwrite '\n' with '\0'
*/
kvpair_t * fillKVpair(char * line){
  kvpair_t * kvPair = malloc(sizeof(kvpair_t));
  const char * eqPtr = strchr(line, '=');
  const char * spacePtr = strchr(line, '\n');

  kvPair->key = malloc((eqPtr - line + 1)*sizeof(char));
  strncpy(kvPair->key, line, eqPtr -line);
  kvPair->key[eqPtr - line] = '\0';

  kvPair->value = malloc((spacePtr - eqPtr)*sizeof(char));
  strncpy(kvPair->value, eqPtr + 1, spacePtr - eqPtr);
  kvPair->value[spacePtr - eqPtr - 1] = '\0';
  
  return kvPair;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname,"r");

  if(f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  //malloc array of KV + size 
  kvarray_t * rKVs = malloc(sizeof(kvarray_t));
  //Initialize array of KV pairs
  rKVs->array = NULL;
  
  char * line = NULL;
  size_t sz;
  rKVs->n = 0;

  while(getline(&line, &sz, f) >= 0){
    //*rKvs->array = *kvpair_t
    //realloc array of pointers to KV_pairs
    rKVs->array = realloc(rKVs->array, (rKVs->n + 1)*sizeof(*rKVs->array));
    //fill i-th KV_pair
    rKVs->array[rKVs->n] = fillKVpair(line);
    rKVs->n++;
  }
  
  free(line);
  
  if(fclose(f) != 0){
    perror("Failed to close file");
    exit(EXIT_FAILURE);
  }

  return rKVs;
}

void freeKVs(kvarray_t * pairs) {

  for(size_t i = 0; i < pairs->n; i++){
    free(pairs->array[i]->key);
    free(pairs->array[i]->value);
    free(pairs->array[i]);
  }

  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {

  for(size_t i = 0; i < pairs->n; i++){
    printf("key = '%s' value = '%s'\n",
	   pairs->array[i]->key,pairs->array[i]->value);
  }

}

char * lookupValue(kvarray_t * pairs, const char * key) {

  for(size_t i = 0; i < pairs->n; i++){
    if(strcmp(key,pairs->array[i]->key) == 0){
      return pairs->array[i]->value;
    }
  }

  return NULL;
}
