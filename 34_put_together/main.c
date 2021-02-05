#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

void fillCounts(counts_t * c, kvarray_t * kv, FILE * f){
  char * line = NULL;
  size_t sz;

  while(getline(&line, &sz, f) >= 0){
    char * p = strchr(line,'\n');
    if(p != NULL){
      *p = '\0';
    }
    char * value = lookupValue(kv,line);
    addCount(c,value);
  }

  free(line);
}


counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * c = createCounts();

  FILE * f = fopen(filename,"r");

  if(f == NULL){
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  fillCounts(c, kvPairs, f);

  if(fclose(f) != 0){
    perror("Failed to close the file");
    exit(EXIT_FAILURE);
  }
  
  return c;
}

int main(int argc, char ** argv) {
  //Check args errors
  if(argc <= 2){
    perror("Need at least 2 files as arguments\n"); 
    return EXIT_FAILURE;
  }

  //read key/value pairs from first file
  kvarray_t * kv = readKVs(argv[1]);
  
  for(int i = 2; i < argc; i++){
    counts_t * c = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);

    FILE * f = fopen(outName, "w");
    if (f == NULL){
      perror("Could not creat file %s\n");
      return EXIT_FAILURE;
    }

    printCounts(c,f);

    if(fclose(f) != 0){
      return EXIT_FAILURE;
    }

    free(outName);
    freeCounts(c);
  }

  freeKVs(kv);

  return EXIT_SUCCESS;
}
