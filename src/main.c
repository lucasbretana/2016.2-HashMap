#include <stdio.h>
#include "usefull.h"
#include "hashmap.h"
#define HELP "--help"
void printHelp(char *);

int main(int argc, char **argv) {
  if(argc != 2){
    fprintf(stderr, "Must specify the colision method! See --help");
    return INVALID_PARAMETER;
  }

  if(strcomp(argv[1], (char*) HELP) == 0){
    printHelp(argv[0]);
    return SUCCESS;
  }
  char op[7], in[100];
  while(scanf("%s %s", op, in) == 2){
    printf("%s", in);
    printf(" %lld\n", h0(in, length(in)));
  }

 return SUCCESS;
}

void printHelp(char *target){
  printf("Usage: %s [OPTION] < [ENTRY_FILE]\n\n", target);
  printf("Simulate the use of a Hash Map using the speficied method for treating colisin.\n");
  printf("  %s\t\tuse the chaining method.\n", CHAINING);
  printf("  %s\t\tuse the linear method.\n", LINEAR);
  printf("  %s\t\tuse the quadratic method.\n", QUADRATIC);
  printf("  %s\t\tuse the double hash method.\n\n", DOUBLE_HASH);
  printf("  --help\t\tshows this text.\n\n");
  printf("Examples: \n  %s %s < hash_keys.txt\n", target, DOUBLE_HASH);
  printf("  %s %s < keys.txt\n", target, LINEAR);
}
