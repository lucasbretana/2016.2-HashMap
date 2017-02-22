#include <stdio.h>
#include <stdlib.h>

int main(){
  char mat[10][10];
  for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
      mat[i][j] = 'l';

  char **pont = malloc(sizeof(char **) * 10);
  // *pont = malloc(sizeof(char *) * 10);

  // void **pont = malloc(sizeof(char **) * 10);
  // *pont = malloc(sizeof(char *) * 10);

  for(int i=0;i<10;i++){
    *(pont + i) = malloc(sizeof(char *) * 10);
    for(int j=0;j<10;j++){
      *((*pont + i) + j) = 'a';
    }
  }
  for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
      printf("%c", mat[i][j]);

  printf("\n");
  for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
      printf("%c", *((*pont + i) + j));
  

  return 0;
}