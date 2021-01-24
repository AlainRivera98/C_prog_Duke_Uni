#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void freqCount(FILE * f, int * counts){
  int c;

  while((c=fgetc(f)) != EOF){
    if(isalpha(c)){
      c = tolower(c);
      counts[c-'a']++;
    }
  }

}


void breakCrypt(FILE * f){
  int index_ans = 0;
  int largest = 0;
  int counts[26] = {0};

  freqCount(f, counts);

  for(int i = 0; i < 26; i++){
    if(counts[i] > largest){
      largest = counts[i];
      index_ans = i;
    }
  }

  if(index_ans < 4){
    index_ans += 26;
  }
  
  printf("%d\n",index_ans-4);
  
}




int main(int argc, char **argv){

  if(argc!=2){
    fprintf(stderr,"More arguments than needed\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1],"r");
  if(f == NULL){
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  breakCrypt(f);

  if(fclose(f) != 0){
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
