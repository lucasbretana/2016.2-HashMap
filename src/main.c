#include <stdio.h>
#include <stdlib.h>
#include "usefull.h"
#include "hashmap.h"

void printHelp(char *);

int main(int argc, char **argv) {
  ConflictMethods_t *M;
  int HASH_SIZE = INITIAL_SIZE;

  M  = malloc(sizeof(ConflictMethods_t));
  if(argc != 2){
    fprintf(stderr, "Must specify the colision M! See --help");
    return INVALID_PARAMETER;
  }

  if(strcomp(argv[1], HELP) == 0){
    printHelp(argv[0]);
    return SUCCESS;
  }
  else if(strcomp(argv[1], CHAINING) == 0)
    *M = Chaining;
  else if(strcomp(argv[1], LINEAR) == 0)
    *M = Linear;
  else if(strcomp(argv[1], QUADRATIC) == 0)
    *M = Quadratic;
  else if(strcomp(argv[1], DOUBLE_HASH) == 0)
     *M = Double_Hash;
  else{
    fprintf(stderr, "Must specify a valid colision M!");
    printHelp(argv[0]);
    return INVALID_PARAMETER;
  }
  const ConflictMethods_t METHOD = *M;
  free(M);
  printf("%d", METHOD);
  //char op[7], in[100];
  //h_code_t code = 0L;
  //position_t pos = 0;
  //while(scanf("%s %s", op, in) == 2){
  //}

  return SUCCESS;
}

void printHelp(char *target){
  printf("Usage: %s [OPTION] < [ENTRY_FILE]\n\n", target);
  printf("Simulate the use of a Hash Map using the speficied M for treating colisions.\n");
  printf("  %s\t\tuse the chaining M.\n", CHAINING);
  printf("  %s\t\tuse the linear M.\n", LINEAR);
  printf("  %s\t\tuse the quadratic M.\n", QUADRATIC);
  printf("  %s\t\tuse the double hash M.\n\n", DOUBLE_HASH);
  printf("  --help\t\tshows this text.\n\n");
  printf("Examples: \n  %s %s < hash_keys.txt\n", target, DOUBLE_HASH);
  printf("  %s %s < hash_keys.txt\n", target, LINEAR);
}
