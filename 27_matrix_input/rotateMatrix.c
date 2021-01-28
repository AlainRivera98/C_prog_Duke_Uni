#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void rotate(char matrix[10][10]); //In rotate.c

void checkMatrix(FILE * f, char matrix[10][10]); 
void printMatrix(char matrix[10][10]);

int main(int argc, char ** argv){

  if(argc != 2){
    char *err_str;
    err_str = (argc > 2)?"More arguments than needed\n":"No file: need arguments\n";
    fprintf(stderr,"%s",err_str);
    return EXIT_FAILURE;
  }

  FILE *f = fopen(argv[1],"r");

  if(f == NULL){
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }

  char matrix[10][10];

  //Fill matrix with file elements if in correct format
  checkMatrix(f, matrix); 
  
  //Print matrix
  //printMatrix(matrix);
  //Rotate matrix
  rotate(matrix);

  //Print rotated matrix
  //printf("\n\n");
  printMatrix(matrix);
  
  return EXIT_SUCCESS;
}


void checkMatrix(FILE * f, char matrix[10][10]){
  int c;
  int i = 0;
  int j = 0;
  int m = 10; //Rows
  int n = 10; //Columns

  while((c=fgetc(f)) != EOF){
    if(c != '\n'){
      if(j >= n){
	perror("Line is too long\n");
	exit(EXIT_FAILURE);
      }
      
      if(i >= m){
	perror("Too many lines in file\n");
	exit(EXIT_FAILURE);
      }

      matrix[i][j] = c;
      j++; //Next char

    } else {
      if(j != n){
	perror("Line is too short\n");
	exit(EXIT_FAILURE);
      }

      i++; //New matrix row
      j = 0; //Reset matrix column
    }
  }

  if(i < m){
    perror("Few lines in file\n");
    exit(EXIT_FAILURE);
  }

}

void printMatrix(char matrix[10][10]){
  int m = 10;
  int n = 10;

  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      printf("%c", matrix[i][j]);
    }
     printf("\n");
  }
}

void rotate(char matrix[10][10]){
  char temp[10][10];

  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      temp[j][10-i-1] = matrix[i][j];
    }
  }

  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      matrix[i][j] = temp[i][j];
    }
  }

}
