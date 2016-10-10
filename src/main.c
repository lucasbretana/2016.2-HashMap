#include <stdio.h>
#include "usefull.h"
#include "hashmap.h"

void printHelp(char *);

int main(int argc, char **argv) {
  if(argc != 2){
    fprintf(stderr, "Must specify the colision method! See --help");
    return INVALID_PARAMETER;
  }

  if(strcomp(argv[1], "--help") == 0){
    printHelp(argv[0]);
    return SUCCESS;
  }

 return SUCCESS;
}

void printHelp(char *target){
  printf("Usage: %s [OPTION] < [ENTRY_FILE]\n", target);
  printf("Simulate the use of a Hash Map using the speficied method for treating colisin.\n");
  printf("  %s\t\tuse the chaining method.\n", CHAINING);
  printf("  %s\t\tuse the linear method.\n", LINEAR);
  printf("  %s\t\tuse the quadratic method.\n", QUADRATIC);
  printf("  %s\t\tuse the double hash method.\n\n", DOUBLE_HASH);
  printf("  --help\t\tshows this text.\n\n");
  printf("Examples: \n  %s %s < hash_keys.txt\n", target, DOUBLE_HASH);
  printf("  %s %s < keys.txt\n", target, LINEAR);
}

