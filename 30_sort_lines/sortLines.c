#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printData(char ** array, size_t n){
  for(size_t i = 0; i < n; i++){
    printf("%s",array[i]);
    free(array[i]);
  }
}

void sortFile(FILE *f){
  char ** array = NULL; //array to store strings
  char * line = NULL; //current string
  size_t sz; //getline will initialize it
  size_t i = 0; //store number of strings
  while(getline(&line,&sz,f) >= 0){
    array = realloc(array,(i+1)*sizeof(*array));
    array[i] = line;
    line = NULL;
    i++;
  }

  free(line);
  sortData(array, i);
  printData(array, i);
  free(array);
}

int main(int argc, char ** argv) {
  
  if(argc <= 0){
    perror("Strange mistake found");
    return EXIT_FAILURE;

  } else if (argc == 1){
    //Read from standart input and sort
    sortFile(stdin);

  } else {
    //Read all inputs and sort them
    for(int i = 1; i < argc; i++){
      FILE * f = fopen(argv[i],"r");
      
      if (f == NULL){
	perror("Could not open file");
	return EXIT_FAILURE;
      }

      //print the sorted file
      sortFile(f);

      if (fclose(f) != 0){
	perror("Failed to close file number %d,i");
	return EXIT_FAILURE;
      }
    }
  }
  
  return EXIT_SUCCESS;
}
