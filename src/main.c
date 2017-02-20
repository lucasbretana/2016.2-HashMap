#include <stdio.h>
#include <stdlib.h>
#include "usefull.h"
#include "hashmap.h"

// Operations
#define GET "GET"
#define DELETE "DELETE"
#define INSERT "INSERT"

// Errors
#define SUCCESS 0
#define INVALID_PARAMETER 1

// Local functions
void printHelp(char *);

// Global (for real) variables
int HASH_SIZE = INITIAL_SIZE;
ConflictMethods_t METHOD;

int main(int argc, char **argv) {
  if(argc != 2){
    fprintf(stderr, "Must specify the colision method! See --help");
    return INVALID_PARAMETER;
  }

  if(strcomp(argv[1], HELP) == 0){
    printHelp(argv[0]);
    return SUCCESS;
  }
  else if(strcomp(argv[1], CHAINING) == 0)
    METHOD = Chaining;
  else if(strcomp(argv[1], LINEAR) == 0)
    METHOD = Linear;
  else if(strcomp(argv[1], QUADRATIC) == 0)
    METHOD = Quadratic;
  else if(strcomp(argv[1], DOUBLE_HASH) == 0)
     METHOD = Double_Hash;
  else{
    fprintf(stderr, "Must specify a valid colision M!");
    printHelp(argv[0]);
    return INVALID_PARAMETER;
  }
/*
 * void hash_delete(key *);
 * void hash_insert(key *);
 * void hash_get(key *);
 */
  char op[7];
  key in[100];
  while(scanf("%s %s", op, in) == 2) {
    if(strcomp(op, DELETE) == 0)
      hash_delete(in);
    else if(strcomp(op, INSERT) == 0)
      hash_insert(in);
    else if(strcomp(op, GET) == 0)
      hash_get(in);
    else
      fprintf(stderr, "Invalid operation (%s).", op);
  }

  return SUCCESS;
}

/**
 * Just print the help option
 */
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
